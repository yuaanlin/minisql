#include "Interpreter.h"
#include "string"
#include <fstream>

using namespace std;

void Interpreter::init(API *a) { api = a; }

ExecutionResponse Interpreter::execute(string sqlCommand) {
    string operation = getWord(sqlCommand, 0);
    ExecutionResponse res;

    if (isSame(operation, "SELECT")) {
        /* Parse SELECT paramters and call API */
        res.error = "SELECT operation not implement yet.";
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

string Interpreter::getWord(string s, int from) {
    string r = "";
    int t = from;
    while (s.at(t) != ' ') {
        r.push_back(s.at(t));
        t++;
    }
    return r;
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