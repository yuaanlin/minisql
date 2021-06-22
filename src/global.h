#ifndef __minisql_global_h__
#define __minisql_global_h__

#include <string>
#include <vector>

using namespace std;

enum DataType { Integer, Float, String };
typedef vector<vector<string>> Records;
enum ErrorType { EOF_REACHED };
enum CreateTableOperationError { TABLE_ALREADY_EXIST };
enum SelectOperationError { SELECTING_TABLE_NOT_EXIST };
enum DeleteOperationError { DELETING_TABLE_NOT_EXIST };
enum InsertOperationError { INSERTING_TABLE_NOT_EXIST };
enum UpdateOperationError { UPDATED_TABLE_NOT_EXIST };
enum CreateIndexOperationError {
    INDEX_ALREADY_EXIST,
    CREATED_INDEX_TABLE_NOT_EXIST,
    CREATED_INDEX_FIELD_NOT_EXIST
};
enum DropIndexOperationError {
    REMOVE_INDEX_FILE_FAILED,
    DROPING_INDEX_NOT_EXIST
};
enum DropTableOperationError {
    REMOVE_TABLE_FILE_FAILED,
    DROPING_TABLE_NOT_EXIST
};

#endif