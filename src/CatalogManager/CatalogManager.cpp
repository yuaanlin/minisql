#include "CatalogManager.h"
#include <fstream>
#include <filesystem>
#include <vector>
#include <stdio.h>

namespace fs = std::filesystem;

void CatalogManager::init(FileLogger *l) {
    logger = l;

    logger->log("Catalog Manager Starting read table metadata files");

    readTableFiles();

    logger->log("Catalog Manager Starting read index metadata files");

    readIndexFiles();
}

vector<Table> CatalogManager::getTables() {
    vector<Table> tables;
    for (auto table : this->tables) {
        tables.push_back(table.second);
    }
    return tables;
}

void CatalogManager::createTable(Table table) {
    if (isTableExist(table.name)) throw TABLE_ALREADY_EXIST;
    this->tables[table.name] = table;
    ofstream tableMetaFile;
    tableMetaFile.open("metadata/table_" + table.name + ".yaml");
    tableMetaFile << "name: " << table.name << endl;
    tableMetaFile << "attributes: " << endl;
    for (auto a : table.attributes) {
        tableMetaFile << "\t- name: " << a.name << endl;
        tableMetaFile << "\t  type: " << a.dataType << endl;
    }
    tableMetaFile.close();
}

bool CatalogManager::isTableExist(string tableName) {
    return tables.find(tableName) != tables.end();
}

void CatalogManager::readTableFiles() {
    logger->log("CatalogManager starting readTableFile ...");

    if (!fs::is_directory("metadata")) {
        logger->log("Folder metadata not found, creating ....");
        fs::create_directory("metadata");
    }

    for (auto &p : fs::recursive_directory_iterator("metadata")) {
        string fileName = p.path().stem().string();
        string ext = p.path().extension();

        if (ext == ".yaml" && fileName.rfind("table_", 0) == 0) {
            logger->log("Found table file " + fileName + ext);

            Table *t = new Table();

            ifstream f;

            f.open("metadata/" + fileName + ext);

            string line;

            Attribute *a = new Attribute();

            while (getline(f, line)) {
                if (line.rfind("name: ", 0) == 0) {
                    string tableName = line.substr(6, line.size() - 5);
                    t->name = tableName;
                }

                if (line.rfind("\t- name: ", 0) == 0) {
                    string attrName = line.substr(9, line.size() - 8);
                    a = new Attribute();
                    a->name = attrName;
                }

                if (line.rfind("\t  type: ", 0) == 0) {
                    string attrType = line.substr(9, 1);
                    if (attrType == "0") a->dataType = Integer;
                    if (attrType == "1") a->dataType = Float;
                    if (attrType == "2") a->dataType = String;
                    t->attributes.push_back(*a);
                }
            }

            logger->log("Table " + t->name +
                        " load from file by CatalogManager successfully");

            this->tables[t->name] = *t;
        }
    }
}

void CatalogManager::dropTable(string tableName) {
    logger->log("CatalogManager starting drop table");

    if (!isTableExist(tableName)) throw DROPING_TABLE_NOT_EXIST;

    logger->log("Removing table yaml file ...");

    if (remove(("metadata/table_" + tableName + ".yaml").c_str()) != 0)
        throw REMOVE_INDEX_FILE_FAILED;

    logger->log("Removing table from hashmap ...");

    this->tables.erase(tableName);

    logger->log("CatalogManager drop table finished.");
}

void CatalogManager::createIndex(Index i) {
    logger->log("Catalog Manager starting create index.");

    if (isIndexExist(i.indexName)) throw INDEX_ALREADY_EXIST;

    this->indexes[i.indexName] = i;

    ofstream tableMetaFile;

    tableMetaFile.open("metadata/index_" + i.indexName + ".yaml");

    tableMetaFile << "name: " << i.indexName << endl;
    tableMetaFile << "table: " << i.tableName << endl;
    tableMetaFile << "type: " << i.dataType << endl;

    tableMetaFile.close();

    logger->log("Catalog Manager create index finished.");
}

bool CatalogManager::isIndexExist(string indexName) {
    return indexes.find(indexName) != indexes.end();
}

void CatalogManager::readIndexFiles() {
    logger->log("CatalogManager starting readIndexFile ...");

    if (!fs::is_directory("metadata")) {
        logger->log("Folder metadata not found, creating ....");
        fs::create_directory("metadata");
    }

    for (auto &p : fs::recursive_directory_iterator("metadata")) {
        string fileName = p.path().stem().string();
        string ext = p.path().extension();
        if (ext == ".yaml" && fileName.rfind("index_", 0) == 0) {
            logger->log("Found index file " + fileName + ext);
            Index *i = new Index();
            ifstream f;
            f.open("metadata/" + fileName + ext);
            string line;
            Attribute *a = new Attribute();
            while (getline(f, line)) {
                if (line.rfind("name: ", 0) == 0) {
                    string indexName = line.substr(6, line.size() - 5);
                    i->indexName = indexName;
                }
                if (line.rfind("table: ", 0) == 0) {
                    string tableName = line.substr(7, line.size() - 6);
                    i->tableName = tableName;
                }
                if (line.rfind("type: ", 0) == 0) {
                    string attrType = line.substr(6, line.size() - 5);
                    if (attrType == "0") i->dataType = Integer;
                    if (attrType == "1") i->dataType = Float;
                    if (attrType == "2") i->dataType = String;
                }
            }
            logger->log("Index " + i->indexName +
                        " load from file by CatalogManager successfully");
            this->indexes[i->indexName] = *i;
        }
    }
}

void CatalogManager::dropIndex(string indexName) {
    if (!isIndexExist(indexName)) throw DROPING_INDEX_NOT_EXIST;

    if (remove(("metadata/index_" + indexName + ".yaml").c_str()) != 0)
        throw REMOVE_INDEX_FILE_FAILED;

    this->indexes.erase(indexName);
}

Table CatalogManager::getTable(string tableName) {
    logger->log("Catalog Manager starting finding table  " + tableName +
                " from hashmap");

    return this->tables.find(tableName)->second;
}

Index CatalogManager::getIndex(string indexName) {
    return this->indexes.find(indexName)->second;
}

DataType CatalogManager::getDataTypeOfAttribute(string tableName,
                                                string fieldName) {
    logger->log("Catalog Manager starting finding datatype of field " +
                fieldName + " in table " + tableName);

    Table t = getTable(tableName);

    for (auto attr : t.attributes) {
        if (attr.name == fieldName) {
            logger->log("Found type " + to_string(attr.dataType));
            return attr.dataType;
        }
    }

    logger->log("Field not found.");
    throw ATTRIBUTE_NOT_FOUND;
}