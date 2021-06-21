#ifndef __minisql_global_h__
#define __minisql_global_h__

#include <string>
#include <vector>

using namespace std;

enum DataType { Integer, Float, String };
typedef vector<vector<string>> Records;
enum ErrorType { EOF_REACHED };
enum CreateTableOperationError { TABLE_ALREADY_EXIST };
enum SelectOperationError { SELECTED_TABLE_NOT_EXIST };
enum InsertOperationError { INSERTED_TABLE_NOT_EXIST };
enum CreateIndexOperationError { CREATED_INDEX_TABLE_NOT_EXIST };
enum UpdateOperationError { UPDATED_TABLE_NOT_EXIST };

#endif