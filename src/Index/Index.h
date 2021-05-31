#ifndef __minisql_index_h__
#define __minisql_index_h__

#include <string>

using namespace std;

class Index {
   private:
    string indexName;
    string tableName;
    string attributeName;
    int dataType;

   public:
    Index(string i, string t, string a, int dt);
    string getName();
    string getTableName();
    string getAttributeName();
    int getDataType();
};

#endif