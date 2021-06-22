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
        throw SELECTING_TABLE_NOT_EXIST;

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
        throw INSERTING_TABLE_NOT_EXIST;

    // TODO: Call Record Manager to insert record
}

void API::createIndex(string indexName, string tableName,
                      vector<string> fields) {
    logger->log("API starting create index.");

    if (!catalogManager->isTableExist(tableName))
        throw CREATED_INDEX_TABLE_NOT_EXIST;

    if (catalogManager->isIndexExist(tableName)) throw INDEX_ALREADY_EXIST;

    logger->log("API validated create index request.");

    for (auto f : fields) {
        DataType dt;

        try {
            dt = catalogManager->getDataTypeOfAttribute(tableName, f);
        } catch (CatalogManager::CatalogManagerError error) {
            throw CREATED_INDEX_FIELD_NOT_EXIST;
        }

        Index *i = new Index();

        i->indexName = indexName;
        i->tableName = tableName;
        i->attributeName = f;
        i->dataType = dt;

        catalogManager->createIndex(*i);
    }

    // TODO: Call IndexManager to create Indexes

    logger->log("API create index finished.");
}

void API::updateRecord(string tableName, vector<string> fields,
                       vector<string> values, vector<Condition> conditions) {
    // TODO: Check table exist

    // TODO: Check fields exist

    // TODO: Call RecordManager to update records
}

void API::deleteRecord(string tableName, vector<Condition> conditions) {
    if (!catalogManager->isTableExist(tableName))
        throw DELETING_TABLE_NOT_EXIST;
}

void API::dropIndex(string indexName) {
    if (!catalogManager->isIndexExist(indexName)) throw DROPING_INDEX_NOT_EXIST;

    catalogManager->dropIndex(indexName);

    // TODO: Call IndexManager::DropIndex
}

void API::dropTable(string tableName) {
    logger->log("API starting drop table");

    if (!catalogManager->isTableExist(tableName)) throw DROPING_TABLE_NOT_EXIST;

    catalogManager->dropTable(tableName);

    // TODO: Call RecordManager::droptable
    // recordManager->dropTable(tableName);

    logger->log("API drop table finished");
}
