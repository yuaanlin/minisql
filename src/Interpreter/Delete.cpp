#include "Interpreter.h"

ExecutionResponse Interpreter::interpretDeleteOperation(string sqlCommand,
                                                        int *p) {
    string w = getWord(sqlCommand, p);

    if (!isSame(w, "FROM")) {
        ExecutionResponse res;
        res.error = "Expect FROM after DELETE but got " + w;
        return res;
    }

    string tableName = getWord(sqlCommand, p);

    if (isKeyword(tableName)) {
        ExecutionResponse res;
        res.error = "Expect table name after FROM but got " + tableName;
        return res;
    }

    vector<Condition> conditions;
    string w = getWord(sqlCommand, p);

    if (!isSame(w, "WHERE") && w != "" && w != ";") {
        ExecutionResponse res;
        res.error = "Expect WHERE or nothing after table name but got " + w;
        return res;
    }

    if (isSame(w, "WHERE")) {
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

    api->deleteRecord(tableName, conditions);

    ExecutionResponse res;
    res.error = "Delete operation not implemented yet!";
    return res;
}