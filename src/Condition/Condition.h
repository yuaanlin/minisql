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
    const static int EQ_OPERATOR = 0;   // =
    const static int NEQ_OPERATOR = 1;  // <>
    const static int BT_OPERATOR = 2;   // >
    const static int LT_OPERATOR = 3;   // <
    const static int BTE_OPERATOR = 4;  // >=
    const static int LTE_OPERATOR = 5;  // <=
    Condition(string a, char o, string v);
};

#endif