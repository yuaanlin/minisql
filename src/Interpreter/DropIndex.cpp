#include "Interpreter.h"

OneCommandExecutionResponse Interpreter::interpretDropIndexOperation(
    string sqlCommand, int *p) {
    OneCommandExecutionResponse res;

    res.cmd = sqlCommand;

    string indexName = getWord(sqlCommand, p);

    if (indexName == "" || isKeyword(indexName)) {
        res.msg = "Expect index name but got " + indexName;
        return res;
    }

    try {
        api->dropIndex(indexName);
        res.msg = "Drop index successfully.";
        return res;
    } catch (DropIndexOperationError error) {
        res.msg = "Unknow error occurred.";
        switch (error) {
            case DROPING_INDEX_NOT_EXIST:
                res.msg = "Index with name " + indexName + " not exist.";
                break;
            case REMOVE_INDEX_FILE_FAILED:
                res.msg = "CatalogManager failed to remove metadata file.";
                break;
        }
        return res;
    }
}