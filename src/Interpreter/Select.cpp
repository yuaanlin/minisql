#include "Interpreter.h"

OneCommandExecutionResponse Interpreter::interpretSelectOperation(
    string sqlCommand, int *p) {
    OneCommandExecutionResponse res;
    res.cmd = sqlCommand;

    vector<string> cols;
    string col;

    while (col = getWord(sqlCommand, p), !isKeyword(col)) {
        cols.push_back(col);
    }

    if (!isSame(col, "FROM")) {
        res.msg =
            "Expected FROM but got " + col + " at position " + to_string(*p);
        return res;
    }

    string tableName = getWord(sqlCommand, p);

    if (isKeyword(tableName)) {
        res.msg = "Expected table name but got " + col + " at position " +
                  to_string(*p);
        return res;
    }

    vector<Attribute> attributes =
        this->catalogManager->getTable(tableName).attributes;

    vector<Condition> conditions;
    string w = getWord(sqlCommand, p);

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

    vector<Attribute> selectedAttrs;
    for (auto col : cols) {
        for (auto attr : attributes) {
            if (attr.name == col) {
                selectedAttrs.push_back(attr);
                break;
            }
        }
    }

    try {
        res.fields = (cols.size() == 1 && cols.at(0) == "*") ? attributes
                                                             : selectedAttrs;
        res.results = this->api->selectRecords(tableName, cols, conditions);
        res.msg = "found " + to_string(res.results.size()) + " results";
        return res;
    } catch (SelectOperationError error) {
        switch (error) {
            case SELECTING_TABLE_NOT_EXIST:
                res.msg = "Table with name " + tableName + " not exist.";
                return res;
                break;
        }
    }
}