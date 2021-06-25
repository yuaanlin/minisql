#include "Interpreter.h"

ExecutionResponse Interpreter::interpretDropIndexOperation(string sqlCommand,
                                                           int *p) {
    string indexName = getWord(sqlCommand, p);

    if (indexName == "" || isKeyword(indexName)) {
        ExecutionResponse res;
        res.error = "Expect index name but got " + indexName;
        return res;
    }

    try {
        api->dropIndex(indexName);
        ExecutionResponse res;
        res.error = "Drop index successfully.";
        return res;
    } catch (DropIndexOperationError error) {
        ExecutionResponse res;
        res.error = "Unknow error occurred.";
        switch (error) {
            case DROPING_INDEX_NOT_EXIST:
                res.error = "Index with name " + indexName + " not exist.";
                break;
            case REMOVE_INDEX_FILE_FAILED:
                res.error = "CatalogManager failed to remove metadata file.";
                break;
        }
        return res;
    }
}