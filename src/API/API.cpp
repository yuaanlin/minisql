#include "API.h"

void API::init(Interpreter *it, CatalogManager *c, RecordManager *r,
               IndexManager *ind) {
    interpreter = it;
    catalogManager = c;
    recordManager = r;
    indexManager = ind;
}