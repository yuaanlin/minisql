#include "API.h"

void API::init(CatalogManager *c, RecordManager *r, IndexManager *ind,
               FileLogger *l) {
    catalogManager = c;
    recordManager = r;
    indexManager = ind;
    logger = l;
}

Records API::selectRecords(string tableName, vector<string> columns,
                           vector<Condition> conditions) {
    if (!catalogManager->isTableExist(tableName))
        throw SELECTED_TABLE_NOT_EXIST;

    // TODO: Check field in conditions exist

    // TODO: Call IndexManager to get possible index

    // TODO: Call RecordManager to get Records

    Records r;
    return r;
}

void API::createTable(string tableName, vector<Attribute> attrs) {
    logger->log("API creating table ...");
    Table t(tableName, attrs);
    catalogManager->createTable(t);

    // TODO: Call IndexManager to create Primary Key index

    // TODO: Call RecordManager to create data file
}

void API::insertRecord(string tableName, vector<string> values) {
    if (!catalogManager->isTableExist(tableName))
        throw INSERTED_TABLE_NOT_EXIST;

    // TODO: Call Record Manager to insert record
}

void API::createIndex(string indexName, string tableName,
                      vector<string> fields) {
    if (!catalogManager->isTableExist(tableName))
        throw CREATED_INDEX_TABLE_NOT_EXIST;

    // TODO: Check fields exist

    // TODO: Check if index name already taken

    // TODO: Call IndexManager to create Indexes
}

void API::updateRecord(string tableName, vector<string> fields,
                       vector<string> values, vector<Condition> conditions) {
    // TODO: Check table exist

    // TODO: Check fields exist

    // TODO: Call RecordManager to update records
}

void deleteRecord(string tableName, vector<Condition> conditions) {}