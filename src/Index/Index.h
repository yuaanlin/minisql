#ifndef __minisql_index_h__
#define __minisql_index_h__

#include <string>
#include "../global.h"

using namespace std;

class Index {
   public:
    string indexName;
    string tableName;
    string attributeName;
    DataType dataType;
    Index(string i, string t, string a, DataType dt);
    Index();
};

#endif