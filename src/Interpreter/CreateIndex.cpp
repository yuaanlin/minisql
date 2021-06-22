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
        ExecutionResponse res;
        res.error = "Index is created successfully.";
        return res;
    } catch (CreateIndexOperationError error) {
        ExecutionResponse res;
        switch (error) {
            case CREATED_INDEX_TABLE_NOT_EXIST:
                res.error = "Table with name " + tableName + " not exist";
                break;
            case INDEX_ALREADY_EXIST:
                res.error = "Index with name " + indexName + " already exist";
                break;
            case CREATED_INDEX_FIELD_NOT_EXIST:
                res.error = "Field(s) for creating index not found.";
                break;
            default:
                res.error = "Create index operation not implemented yet!";
                break;
        }
        return res;
    }
}