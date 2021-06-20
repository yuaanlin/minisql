#ifndef __minisql_global_h__
#define __minisql_global_h__

#include <string>
#include <vector>

using namespace std;

enum DataType { Integer, Float, String };
typedef vector<vector<string>> Records;
enum ErrorType { EOF_REACHED = -1, TABLE_ALREADY_EXIST = -2 };

#endif