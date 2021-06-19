#include "../Condition/Condition.h"
#include "Interpreter.h"
#include "string"
#include <fstream>
#include <vector>
#include <fstream>

using namespace std;

void Interpreter::init(API *a) { api = a; }

ExecutionResponse Interpreter::execute(string sqlCommand) {
    replace(sqlCommand.begin(), sqlCommand.end(), ',', ' ');

    int p = 0;
    string operation = getWord(sqlCommand, &p);
    ExecutionResponse res;

    if (isSame(operation, "SELECT")) {
        vector<string> cols;
        string col;

        while (col = getWord(sqlCommand, &p), !isKeyword(col)) {
            cols.push_back(col);
        }

        vector<Attribute> attributes;
        // TODO: Get attributes from Catalog Manager

        if (!isSame(col, "FROM")) {
            res.error =
                "Expected FROM but got " + col + " at position " + to_string(p);
            return res;
        }

        string tableName = getWord(sqlCommand, &p);

        if (isKeyword(tableName)) {
            res.error = "Expected table name but got " + col + " at position " +
                        to_string(p);
            return res;
        }

        vector<Condition> conditions;
        string w;

        try {
            w = getWord(sqlCommand, &p);
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
                    w = getWord(sqlCommand, &p);
                } catch (ErrorType err) {
                    if (err == EOF_REACHED) break;
                }

                if (isSame(w, "AND")) {
                    continue;
                }

                if (isSame(w, "OR")) {
                    res.error =
                        "Our MiniSQL has not implement OR condition yet!";
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

        res.results = this->api->selectRecords(tableName, cols, conditions);
        res.fields = attributes;

        return res;
    }

    if (isSame(operation, "INSERT")) {
        /* Parse INSERT paramters and call API */
        res.error = "INSERT operation not implement yet.";
        return res;
    }

    if (isSame(operation, "UPDATE")) {
        /* Parse UPDATE paramters and call API */
        res.error = "UPDATE operation not implement yet.";
        return res;
    }

    if (isSame(operation, "DELETE")) {
        /* Parse DELETE paramters and call API */
        res.error = "DELETE not implement yet.";
        return res;
    }

    if (isSame(operation, "DROP")) {
        /* Parse DROP paramters and call API */
        res.error = "DROP operation not implement yet.";
        return res;
    }

    throw "ERROR_UNKNOWN_OPERATION";
}

string Interpreter::getWord(string s, int *from) {
    if (s.size() <= *from) throw EOF_REACHED;

    while (s.size() > *from + 1 && s.at(*from) == ' ') {
        (*from)++;
    }

    bool currentIsLetter = isLetter(s.at(*from));

    string r = "";

    while (s.size() > *from && s.at(*from) != ' ' &&
           currentIsLetter == isLetter(s.at(*from))) {
        r.push_back(s.at(*from));
        (*from)++;
    }

    while (s.size() > *from && s.at(*from) == ' ') {
        (*from)++;
    }

    return r;
}

bool Interpreter::isLetter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c >= 'Z');
}

bool Interpreter::isSame(string a, string b) {
    for (int i = 0; i < (a.length()); i++) a[i] = toupper(a[i]);
    for (int i = 0; i < (b.length()); i++) b[i] = toupper(b[i]);
    return a.compare(b) == 0;
}

string ExecutionResponse::getJson() {
    string r = "{";

    /* Print results */
    r.append("\"results\": [");
    for (auto res : this->results) {
        r.append("[");
        bool firstCol = true;
        for (auto resCol : res) {
            if (!firstCol) {
                r.append(",");
            }
            firstCol = false;
            r.append(resCol);
        }
        r.append("]");
    }
    r.append("],");

    /* Print fields */
    r.append("\"fields\": [");
    for (auto f : this->fields) {
        r.append("{");
        r.append("\"name\": " + f.name);
        string d;
        switch (f.dataType) {
            case DataType::Float:
                d = "float";
                break;
            case DataType::Integer:
                d = "int";
                break;
            case DataType::String:
                d = "string";
                break;
        }
        r.append(",\"type\": " + d);
        r.append("}");
    }
    r.append("],");

    /* Print error */
    r.append("\"error\": \"" + this->error + "\"");

    r.append("}");
    return r;
}

bool Interpreter::isKeyword(string a) {
    if (isSame(a, "SELECT")) return true;
    if (isSame(a, "FROM")) return true;
    if (isSame(a, "CREATE")) return true;
    if (isSame(a, "TABLE")) return true;
    if (isSame(a, "DATABASE")) return true;
    if (isSame(a, "VALUES")) return true;
    if (isSame(a, "INSERT")) return true;
    if (isSame(a, "INTO")) return true;
    if (isSame(a, "WHERE")) return true;
    if (isSame(a, "DROP")) return true;
    if (isSame(a, "DELETE")) return true;
    if (isSame(a, "INDEX")) return true;
    if (isSame(a, "int")) return true;
    if (isSame(a, "float")) return true;
    if (isSame(a, "string")) return true;
    return false;
}

void Interpreter::log(string s) {
    ofstream log;
    log.open("log.txt", fstream::in | fstream::out | fstream::app);
    log << s << endl;
    log.close();
}