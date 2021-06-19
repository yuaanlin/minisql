#include "API.h"

void API::init(CatalogManager *c, RecordManager *r, IndexManager *ind) {
    catalogManager = c;
    recordManager = r;
    indexManager = ind;
}

Records API::selectRecords(string tableName, vector<string> columns,
                           vector<Condition> conditions) {
    Records r;
    return r;
}