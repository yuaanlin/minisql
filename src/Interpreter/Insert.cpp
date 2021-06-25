#include "Interpreter.h"

ExecutionResponse Interpreter::interpretInsertOperation(string sqlCommand,
                                                        int *p) {
    string w = getWord(sqlCommand, p);

    if (!isSame(w, "INTO")) {
        ExecutionResponse res;
        res.error = "Expect INTO after INSERT but got " + w;
        return res;
    }

    string tableName = getWord(sqlCommand, p);

    w = getWord(sqlCommand, p);

    if (!isSame(w, "VALUES")) {
        ExecutionResponse res;
        res.error = "Expect VALUES after table name but got " + w;
        return res;
    }

    w = getWord(sqlCommand, p);

    if (!isSame(w, "(")) {
        ExecutionResponse res;
        res.error = "Expect ( after VALUES but got " + w;
        return res;
    }

    vector<string> values;

    while (w = getWord(sqlCommand, p), w.rfind(")", 0) != 0) {
        values.push_back(w);
    }

    try {
        api->insertRecord(tableName, values);
        ExecutionResponse res;
        res.error = "Insert successfully.";
        return res;
    } catch (InsertOperationError error) {
        switch (error) {
            case INSERTING_TABLE_NOT_EXIST:
                ExecutionResponse res;
                res.error = "Table with name " + tableName + " not exist.";
                return res;
                break;
        }
    }
}