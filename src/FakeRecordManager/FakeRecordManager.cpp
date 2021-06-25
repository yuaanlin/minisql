#include "FakeRecordManager.h"
#include <fstream>
#include <filesystem>
#include "iostream"
#include <stdio.h>

namespace fs = std::filesystem;

#define RECORD_PER_BLOCK 60

void FakeRecordManager::init(FileLogger *l, CatalogManager *c) {
    this->catalogManager = c;
    this->logger = l;

    vector<Table> tables = this->catalogManager->getTables();
    vector<string> tableNames;
    for (auto t : tables) {
        tableNames.push_back(t.name);
    }

    this->readTablesFromFiles(tableNames);
}

void FakeRecordManager::saveTablesToFiles() {
    logger->log("Saving table files ...");

    if (!fs::is_directory("data")) {
        fs::create_directory("data");
    }

    for (auto table : this->tables) {
        logger->log("Saving table " + table.first + " ...");
        ofstream data("./data/" + table.first + ".db", ios::binary);
        unsigned int tableFileTotalSize = 0;
        for (auto block : table.second) {
            for (auto record : block) {
                unsigned int recordSize = 0;

                for (auto col : record) {
                    for (auto c : col) {
                        recordSize++;
                    }
                    recordSize++;
                }
                recordSize++;

                char *buffer = new char[recordSize];

                int idx = 0;
                for (auto col : record) {
                    for (auto c : col) {
                        buffer[idx++] = c;
                    }
                    buffer[idx++] = '\0';
                }

                buffer[idx++] = '\n';
                data.write(buffer, recordSize);
            }
        }
        data.close();
        logger->log("Table file " + table.first + ".db saved");
    }

    logger->log("All table files saved");
}

void FakeRecordManager::readTablesFromFiles(vector<string> tableNames) {
    logger->log("RecordManager starting read data from table files ...");

    if (!fs::is_directory("data")) {
        fs::create_directory("data");
    }

    FakeTable *ft = new FakeTable();
    int count = 0;
    for (auto tableName : tableNames) {
        logger->log("Reading data from data/" + tableName + ".db ...");

        ifstream f;
        f.open("data/" + tableName + ".db");
        FakeRecordBlock *rb = new FakeRecordBlock();
        string line;
        while (getline(f, line)) {
            vector<string> record;
            string temp = "";
            for (auto c : line) {
                if (c == '\0') {
                    record.push_back(temp);
                    temp = "";
                    continue;
                }
                temp.push_back(c);
            }

            if (count % RECORD_PER_BLOCK == 0) {
                ft->push_back(*rb);
                rb = new FakeRecordBlock();
            }

            rb->push_back(record);
            count++;
        }

        ft->push_back(*rb);

        this->tables[tableName] = *ft;

        logger->log("Read data from data/" + tableName + " successfully");
    }

    logger->log("RecordManager read all data from file successfully.");
}

Records FakeRecordManager::selectRecord(string tableName,
                                        vector<Condition> conditions) {
    logger->log("RecordManager starting select records ...");

    FakeTable table = this->tables[tableName];

    logger->log("RecordManager starting select records ...");

    Table t = this->catalogManager->getTable(tableName);

    vector<int> conditionAttrIndex;

    for (auto c : conditions) {
        int i = 0;
        bool found = false;
        for (auto attr : t.attributes) {
            if (c.attributeName == attr.name) {
                conditionAttrIndex.push_back(i);
                found = true;
                break;
            }
            i++;
        }
        if (!found) {
            throw 1;
        }
    }

    Records r;

    for (auto block : table) {
        for (auto record : block) {
            bool check = true;
            for (int i = 0; i < conditionAttrIndex.size(); i++) {
                switch (conditions[i].operate) {
                    case Condition::EQ_OPERATOR:
                        if (record[conditionAttrIndex[i]] !=
                            conditions[i].value)
                            check = false;
                        break;
                    case Condition::NEQ_OPERATOR:
                        if (record[conditionAttrIndex[i]] ==
                            conditions[i].value)
                            check = false;
                        break;
                    case Condition::LT_OPERATOR:
                        if (record[conditionAttrIndex[i]] >=
                            conditions[i].value)
                            check = false;
                        break;
                    case Condition::LTE_OPERATOR:
                        if (record[conditionAttrIndex[i]] > conditions[i].value)
                            check = false;
                        break;
                    case Condition::BT_OPERATOR:
                        if (record[conditionAttrIndex[i]] <=
                            conditions[i].value)
                            check = false;
                        break;
                    case Condition::BTE_OPERATOR:
                        if (record[conditionAttrIndex[i]] < conditions[i].value)
                            check = false;
                        break;
                }
            }
            if (check) r.push_back(record);
        }
    }

    logger->log("Found " + to_string(r.size()) + " matched records");

    return r;
}

void FakeRecordManager::insertRecord(string tableName, vector<string> record) {
    logger->log("RecordManager starting insert record");

    FakeTable *table = &(this->tables[tableName]);

    logger->log("Found table in record manager");

    if (table->size() == 0) {
        FakeRecordBlock newBlock;
        table->push_back(newBlock);
    }

    FakeRecordBlock *lastBlock = &((*table)[table->size() - 1]);

    logger->log("Got last block");

    if (lastBlock->size() >= RECORD_PER_BLOCK) {
        logger->log("Append new block");

        FakeRecordBlock *newBlock = new FakeRecordBlock();
        table->push_back(*newBlock);
        lastBlock = newBlock;
    }

    logger->log("insert new record to last block");

    lastBlock->push_back(record);
}

void FakeRecordManager::createTable(string tableName) {
    ifstream f;
    f.open("data/" + tableName + ".db");
    f.close();
}

void FakeRecordManager::dropTable(string tableName) {
    remove(("data/" + tableName + ".db").c_str());
}