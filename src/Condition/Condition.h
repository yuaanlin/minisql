#ifndef __minisql_condition_h__
#define __minisql_condition_h__

#include <string>

using namespace std;

/* A query condition */
class Condition {
   private:
    string attributeName;
    char operate;
    string value;

   public:
    const static char EQ_OPERATOR = '=';
    const static char NEQ_OPERATOR = '<>';
    const static char BT_OPERATOR = '>';
    const static char LT_OPERATOR = '<';
    const static char BTE_OPERATOR = '>=';
    const static char LTE_OPERATOR = '<=';
    Condition(string a, char o, string v);
};

#endif