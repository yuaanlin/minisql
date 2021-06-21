#include "../Condition/Condition.h"
#include "Interpreter.h"
#include "string"
#include <fstream>
#include <vector>
#include <fstream>

using namespace std;

void Interpreter::init(API *a, FileLogger *l) {
    api = a;
    logger = l;
}

ExecutionResponse Interpreter::execute(string sqlCommand) {
    logger->log("Received new sql command: ");
    logger->log(sqlCommand);

    replace(sqlCommand.begin(), sqlCommand.end(), ',', ' ');
    replace(sqlCommand.begin(), sqlCommand.end(), '\n', ' ');
    replace(sqlCommand.begin(), sqlCommand.end(), '\"', ' ');
    replace(sqlCommand.begin(), sqlCommand.end(), '\'', ' ');

    int p = 0;
    string operation = getWord(sqlCommand, &p);

    if (isSame(operation, "SELECT")) {
        return interpretSelectOperation(sqlCommand, &p);
    }

    if (isSame(operation, "INSERT")) {
        return interpretInsertOperation(sqlCommand, &p);
    }

    if (isSame(operation, "UPDATE")) {
        return interpretUpdateOperation(sqlCommand, &p);
    }

    if (isSame(operation, "DELETE")) {
        return interpretDeleteOperation(sqlCommand, &p);
    }

    if (isSame(operation, "CREATE")) {
        string target = getWord(sqlCommand, &p);
        if (isSame(target, "INDEX")) {
            return interpretCreateIndexOperation(sqlCommand, &p);
        }

        if (isSame(target, "TABLE")) {
            return interpretCreateTableOperation(sqlCommand, &p);
        }

        ExecutionResponse res;
        res.error = "Expect INDEX or TABLE after CREATE";
        return res;
    }

    if (isSame(operation, "DROP")) {
        string target = getWord(sqlCommand, &p);
        if (isSame(target, "INDEX")) {
            return interpretDropIndexOperation(sqlCommand, &p);
        }

        if (isSame(target, "TABLE")) {
            return interpretDropTableOperation(sqlCommand, &p);
        }

        ExecutionResponse res;
        res.error = "Expect INDEX or TABLE after DROP";
        return res;
    }

    ExecutionResponse res;
    res.error =
        "Got unknow operation, expect CREATE, DROP, INSERT, UPDATE, DELETE or "
        "SELECT, but got " +
        operation;
    return res;
}
