#include "CatalogManager.h"
#include <fstream>
#include <filesystem>
#include <vector>

namespace fs = std::filesystem;

void CatalogManager::init(API *a, FileLogger *l) {
    api = a;
    logger = l;
    readTableFiles();
}

void CatalogManager::createTable(Table table) {
    if (isTableExist(table.name)) throw TABLE_ALREADY_EXIST;
    this->tables[table.name] = table;
    ofstream tableMetaFile;
    tableMetaFile.open("data/table_" + table.name + ".yaml");
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

    for (auto &p : fs::recursive_directory_iterator("data")) {
        string fileName = p.path().stem().string();
        string ext = p.path().extension();
        if (ext == ".yaml" && fileName.rfind("table_", 0) == 0) {
            logger->log("Found table file " + fileName + ext);
            Table *t = new Table();
            ifstream f;
            f.open("data/" + fileName + ext);
            string line;
            Attribute *a = new Attribute();
            while (getline(f, line)) {
                if (line.rfind("name: ", 0) == 0) {
                    string tableName = line.substr(6, line.size() - 5);
                    t->name = tableName;
                }
                if (line.rfind("\t- name: ", 0) == 0) {
                    string attrName = line.substr(10, line.size() - 9);
                    a = new Attribute();
                    a->name = attrName;
                }
                if (line.rfind("\t  type: ", 0) == 0) {
                    string attrType = line.substr(10, line.size() - 9);
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