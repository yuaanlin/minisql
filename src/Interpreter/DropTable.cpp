#include "Interpreter.h"

ExecutionResponse Interpreter::interpretDropTableOperation(string sqlCommand,
                                                           int *p) {
    logger->log("Interpreter starting interpret drop table command");

    string tableName = getWord(sqlCommand, p);

    if (tableName == "" || isKeyword(tableName)) {
        ExecutionResponse res;
        res.error = "Expect table name but got " + tableName;
        return res;
    }

    logger->log("Got table name " + tableName);

    try {
        api->dropTable(tableName);
        ExecutionResponse res;
        res.error = "Drop table successfully.";
        return res;
    } catch (DropTableOperationError error) {
        ExecutionResponse res;
        res.error = "Unknow error occurred.";
        switch (error) {
            case DROPING_TABLE_NOT_EXIST:
                res.error = "Table with name " + tableName + " not exist.";
                break;
            case REMOVE_TABLE_FILE_FAILED:
                res.error = "CatalogManager failed to remove metadata file.";
                break;
        }
        return res;
    }
}