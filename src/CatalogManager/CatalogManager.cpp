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
    this->tables["test"] = Table("test", vector<Attribute>());
    ofstream tableMetaFile;
    tableMetaFile.open("data/table_" + table.name + ".yaml");
    tableMetaFile << "name: " << table.name << endl;
    tableMetaFile << "attributes: " << endl;
    for (auto a : table.attributes) {
        logger->log("qq");
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
        }
    }
}