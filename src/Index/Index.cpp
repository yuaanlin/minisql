#include "Index.h"

Index::Index(string i, string t, string a, DataType dt) {
    indexName = i;
    tableName = t;
    attributeName = a;
    dataType = dt;
}

Index::Index() {}