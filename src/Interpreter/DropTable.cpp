#include "Interpreter.h"

OneCommandExecutionResponse Interpreter::interpretDropTableOperation(
    string sqlCommand, int *p) {
    OneCommandExecutionResponse res;

    res.cmd = sqlCommand;

    logger->log("Interpreter starting interpret drop table command");

    string tableName = getWord(sqlCommand, p);

    if (tableName == "" || isKeyword(tableName)) {
        res.msg = "Expect table name but got " + tableName;
        return res;
    }

    logger->log("Got table name " + tableName);

    try {
        api->dropTable(tableName);
        res.msg = "Drop table successfully.";
        return res;
    } catch (DropTableOperationError error) {
        res.msg = "Unknow error occurred.";
        switch (error) {
            case DROPING_TABLE_NOT_EXIST:
                res.msg = "Table with name " + tableName + " not exist.";
                break;
            case REMOVE_TABLE_FILE_FAILED:
                res.msg = "CatalogManager failed to remove metadata file.";
                break;
        }
        return res;
    }
}