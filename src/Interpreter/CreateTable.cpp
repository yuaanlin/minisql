#include "Interpreter.h"

ExecutionResponse Interpreter::interpretCreateTableOperation(string sqlCommand,
                                                             int *p) {
    ExecutionResponse res;
    res.error = "Create table operation not implemented yet!";
    api->createTable();
    return res;
}