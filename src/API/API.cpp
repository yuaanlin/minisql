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
    Records r;
    return r;
}

void API::createTable() {
    logger->log("API creating table ...");
    string tableName = "test";
    vector<Attribute> attrs;
    logger->log("init");
    attrs.push_back(Attribute("field1", Integer));
    Table t(tableName, attrs);
    logger->log("go to cata");
    catalogManager->createTable(t);
}