#include "Interpreter.h"

ExecutionResponse Interpreter::interpretCreateIndexOperation(string sqlCommand,
                                                             int *p) {
    string indexName = getWord(sqlCommand, p);

    if (isKeyword(indexName)) {
        ExecutionResponse res;
        res.error = "Expect index name but got " + indexName;
        return res;
    }

    string w = getWord(sqlCommand, p);

    if (!isSame(w, "ON")) {
        ExecutionResponse res;
        res.error = "Expect ON after index name but got " + w;
        return res;
    }

    string tableName = getWord(sqlCommand, p);

    if (isKeyword(tableName)) {
        ExecutionResponse res;
        res.error = "Expect table name but got " + tableName;
        return res;
    }

    w = getWord(sqlCommand, p);

    if (!isSame(w, "(")) {
        ExecutionResponse res;
        res.error = "Expect ( after table name but got " + w;
        return res;
    }

    vector<string> indexFields;

    while (w = getWord(sqlCommand, p), w.rfind(")", 0) != 0) {
        indexFields.push_back(w);
    }

    try {
        api->createIndex(indexName, tableName, indexFields);
    } catch (CreateIndexOperationError error) {
        switch (error) {
            case CREATED_INDEX_TABLE_NOT_EXIST:
                ExecutionResponse res;
                res.error = "Table with name " + tableName + " not exist";
                return res;
                break;
        }
    }

    ExecutionResponse res;
    res.error = "Create index operation not implemented yet!";
    return res;
}