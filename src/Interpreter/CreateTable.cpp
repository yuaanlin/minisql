#include "Interpreter.h"

ExecutionResponse Interpreter::interpretCreateTableOperation(string sqlCommand,
                                                             int *p) {
    logger->log("Interpreter starting interpret create table command");

    string tableName = getWord(sqlCommand, p);

    logger->log("Get table name " + tableName);

    vector<Attribute> attrs;

    string w;
    w = getWord(sqlCommand, p);

    if (w != "(") {
        ExecutionResponse res;
        res.error = "Expect fields definition after table name";
        return res;
    }

    int c = 0;
    Attribute *a = new Attribute();
    while (w = getWord(sqlCommand, p), w.rfind(")", 0) != 0) {
        if (c % 3 == 1) {
            a = new Attribute();
            a->name = w;
        }

        if (c % 3 == 2) {
            if (isSame(w, "int")) {
                a->dataType = Integer;
            }
            if (isSame(w, "varchar")) {
                a->dataType = String;
            }
            if (isSame(w, "float")) {
                a->dataType = Float;
            }
            logger->log("Added field " + a->name + " with type " + w);
            attrs.push_back(*a);
        }
        c++;
    }

    try {
        api->createTable(tableName, attrs);
        ExecutionResponse res;
        res.error = "Table with name " + tableName + " created successfully";
        return res;
    } catch (CreateTableOperationError error) {
        ExecutionResponse res;
        switch (error) {
            case TABLE_ALREADY_EXIST:
                res.error = "Table with name " + tableName + " already exist!";
                break;
            default:
                res.error = "Unknow error occurred";
                break;
        }
        return res;
    }
}