#include "Interpreter.h"

OneCommandExecutionResponse Interpreter::interpretDeleteOperation(
    string sqlCommand, int *p) {
    OneCommandExecutionResponse res;

    res.cmd = sqlCommand;

    string w = getWord(sqlCommand, p);

    if (!isSame(w, "FROM")) {
        res.msg = "Expect FROM after DELETE but got " + w;
        return res;
    }

    string tableName = getWord(sqlCommand, p);

    if (isKeyword(tableName)) {
        res.msg = "Expect table name after FROM but got " + tableName;
        return res;
    }

    vector<Condition> conditions;
    w = getWord(sqlCommand, p);

    if (!isSame(w, "WHERE") && w != "" && w != ";") {
        res.msg = "Expect WHERE or nothing after table name but got " + w;
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
                res.msg = "Our MiniSQL has not implement OR condition yet!";
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

    int c = api->deleteRecord(tableName, conditions);
    res.msg = "Delete " + to_string(c) + " records successfully.";
    return res;
}