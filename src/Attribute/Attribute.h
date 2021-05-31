#ifndef __minisql_attribute_h__
#define __minisql_attribute_h__

#include "global.h"
#include "string"

using namespace std;

/** An attribute of entity */
class Attribute {
   private:
    string name;
    DataType dataType;

   public:
    Attribute(string n, DataType dt);
};

#endif