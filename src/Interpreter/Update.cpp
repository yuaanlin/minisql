#include "Interpreter.h"

ExecutionResponse Interpreter::interpretUpdateOperation(string sqlCommand,
                                                        int *p) {
    logger->log("Interpreter starting interpert UPDATE operation");

    string tableName = getWord(sqlCommand, p);

    if (isKeyword(tableName)) {
        ExecutionResponse res;
        res.error = "Expect table name after UPDATE but got " + tableName;
        return res;
    }

    string w = getWord(sqlCommand, p);

    if (!isSame(w, "SET")) {
        ExecutionResponse res;
        res.error = "Expect SET after table name but got " + w;
        return res;
    }

    vector<string> fields;
    vector<string> values;

    int c = 0;
    while (w = getWord(sqlCommand, p), !isSame(w, ";") && !isSame(w, "WHERE")) {
        logger->log(w);
        if (c % 3 == 0) {
            fields.push_back(w);
        }
        if (c % 3 == 1) {
            if (!isSame(w, "=")) {
                ExecutionResponse res;
                res.error = "Expect = after field name but got " + w;
                return res;
            }
        }
        if (c % 3 == 2) {
            values.push_back(w);
        }
        c++;
    }

    vector<Condition> conditions;

    if (isSame(w, "WHERE")) {
        logger->log("Starting parsing conditions ...");
        string a;
        int o;
        string b;
        int c = 0;
        while (true) {
            w = getWord(sqlCommand, p);

            if (w == "" || w == ";") break;

            if (isSame(w, "AND")) {
                continue;
            }

            if (isSame(w, "OR")) {
                ExecutionResponse res;
                res.error = "Our MiniSQL has not implement OR condition yet!";
                return res;
            }

            if (c % 3 == 0) {
                a = w;
            }

            if (c % 3 == 1) {
                if (isSame(w, "=")) o = Condition::EQ_OPERATOR;
                if (isSame(w, ">")) o = Condition::BT_OPERATOR;
                if (isSame(w, "<")) o = Condition::LT_OPERATOR;
                if (isSame(w, ">=")) o = Condition::BTE_OPERATOR;
                if (isSame(w, "<=")) o = Condition::LTE_OPERATOR;
                if (isSame(w, "<>") || isSame(w, "><") || isSame(w, "!="))
                    o = Condition::NEQ_OPERATOR;
            }

            if (c % 3 == 2) {
                b = w;
                Condition *cond = new Condition(a, o, b);
                conditions.push_back(*cond);
            }
            c++;
        }
    }

    try {
        api->updateRecord(tableName, fields, values, conditions);
        ExecutionResponse res;
        res.error = "Updated records successfully.";
        return res;
    } catch (UpdateOperationError error) {
        switch (error) {
            case UPDATED_TABLE_NOT_EXIST:
                ExecutionResponse res;
                res.error = "Table with name " + tableName + " does not exist";
                return res;
                break;
        }
    }

    ExecutionResponse res;
    res.error = "Unknow error occurred";
    return res;
}