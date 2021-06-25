#include "Interpreter.h"

OneCommandExecutionResponse Interpreter::interpretCreateIndexOperation(
    string sqlCommand, int *p) {
    OneCommandExecutionResponse res;

    res.cmd = sqlCommand;

    string indexName = getWord(sqlCommand, p);

    if (isKeyword(indexName)) {
        res.msg = "Expect index name but got " + indexName;
        return res;
    }

    string w = getWord(sqlCommand, p);

    if (!isSame(w, "ON")) {
        res.msg = "Expect ON after index name but got " + w;
        return res;
    }

    string tableName = getWord(sqlCommand, p);

    if (isKeyword(tableName)) {
        res.msg = "Expect table name but got " + tableName;
        return res;
    }

    w = getWord(sqlCommand, p);

    if (!isSame(w, "(")) {
        res.msg = "Expect ( after table name but got " + w;
        return res;
    }

    vector<string> indexFields;

    while (w = getWord(sqlCommand, p), w.rfind(")", 0) != 0) {
        indexFields.push_back(w);
    }

    try {
        api->createIndex(indexName, tableName, indexFields);
        res.msg = "Index is created successfully.";
        return res;
    } catch (CreateIndexOperationError error) {
        switch (error) {
            case CREATED_INDEX_TABLE_NOT_EXIST:
                res.msg = "Table with name " + tableName + " not exist";
                break;
            case INDEX_ALREADY_EXIST:
                res.msg = "Index with name " + indexName + " already exist";
                break;
            case CREATED_INDEX_FIELD_NOT_EXIST:
                res.msg = "Field(s) for creating index not found.";
                break;
            default:
                res.msg = "Create index operation not implemented yet!";
                break;
        }
        return res;
    }
}