#ifndef __minisql_table_h__
#define __minisql_table_h__

#include "../Attribute/Attribute.h"
#include <string>
#include <vector>

class Table {
   public:
    string name;
    vector<Attribute> attributes;
    Table();
    Table(string name, vector<Attribute> attributes);
};

#endif