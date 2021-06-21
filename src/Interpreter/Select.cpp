#include "Interpreter.h"

ExecutionResponse Interpreter::interpretSelectOperation(string sqlCommand,
                                                        int *p) {
    vector<string> cols;
    string col;

    while (col = getWord(sqlCommand, p), !isKeyword(col)) {
        cols.push_back(col);
    }

    vector<Attribute> attributes;
    // TODO: Get attributes from Catalog Manager

    if (!isSame(col, "FROM")) {
        ExecutionResponse res;
        res.error =
            "Expected FROM but got " + col + " at position " + to_string(*p);
        return res;
    }

    string tableName = getWord(sqlCommand, p);

    if (isKeyword(tableName)) {
        ExecutionResponse res;
        res.error = "Expected table name but got " + col + " at position " +
                    to_string(*p);
        return res;
    }

    vector<Condition> conditions;
    string w;

    try {
        w = getWord(sqlCommand, p);
    } catch (int err) {
        // 无条件查询
        if (err == EOF_REACHED) w = "";
    }

    if (isSame(w, "WHERE")) {
        string a;
        int o;
        string b;
        int c = 0;
        while (true) {
            try {
                w = getWord(sqlCommand, p);
            } catch (ErrorType err) {
                if (err == EOF_REACHED) break;
            }

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
        ExecutionResponse res;
        res.fields = attributes;
        res.results = this->api->selectRecords(tableName, cols, conditions);
        return res;
    } catch (SelectOperationError error) {
        switch (error) {
            case SELECTED_TABLE_NOT_EXIST:
                ExecutionResponse res;
                res.error = "Table with name " + tableName + " not exist.";
                return res;
                break;
        }
    }
}