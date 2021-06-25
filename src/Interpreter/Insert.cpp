#include "Interpreter.h"

OneCommandExecutionResponse Interpreter::interpretInsertOperation(
    string sqlCommand, int *p) {
    OneCommandExecutionResponse res;
    res.cmd = sqlCommand;

    string w = getWord(sqlCommand, p);

    if (!isSame(w, "INTO")) {
        res.msg = "Expect INTO after INSERT but got " + w;
        return res;
    }

    string tableName = getWord(sqlCommand, p);

    w = getWord(sqlCommand, p);

    if (!isSame(w, "VALUES")) {
        res.msg = "Expect VALUES after table name but got " + w;
        return res;
    }

    w = getWord(sqlCommand, p);

    if (!isSame(w, "(")) {
        res.msg = "Expect ( after VALUES but got " + w;
        return res;
    }

    vector<string> values;

    while (w = getWord(sqlCommand, p), w.rfind(")", 0) != 0) {
        logger->log(w);
        values.push_back(w);
    }

    try {
        api->insertRecord(tableName, values);
        res.msg = "Insert successfully.";
        return res;
    } catch (InsertOperationError error) {
        switch (error) {
            case INSERTING_TABLE_NOT_EXIST:
                res.msg = "Table with name " + tableName + " not exist.";
                return res;
                break;
        }
    }
}