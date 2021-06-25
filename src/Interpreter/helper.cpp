#include "Interpreter.h"
#include <ctime>
#include <string>

string Interpreter::getWord(string s, int *from) {
    if (s.size() <= *from) return "";

    if (s.at(*from) == '(') {
        (*from)++;
        return "(";
    }

    if (s.at(*from) == ')') {
        (*from)++;
        return ")";
    }

    while (s.size() > *from + 1 && (s.at(*from) == ' ') ||
           (s.at(*from) == (char)255)) {
        (*from)++;
    }

    bool currentIsLetter = isLetter(s.at(*from));

    string r = "";

    while (s.size() > *from && s.at(*from) != ' ' &&
           currentIsLetter == isLetter(s.at(*from))) {
        if (s.at(*from) == ')') {
            break;
        }

        r.push_back(s.at(*from));
        (*from)++;
    }

    while (s.size() > *from && s.at(*from) == ' ') {
        (*from)++;
    }

    return r;
}

bool Interpreter::isLetter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_') ||
           (c >= '0' && c <= '9') || (c == '.') || (c == '-');
}

bool Interpreter::isSame(string a, string b) {
    for (int i = 0; i < (a.length()); i++) a[i] = toupper(a[i]);
    for (int i = 0; i < (b.length()); i++) b[i] = toupper(b[i]);
    return a.compare(b) == 0;
}

string ExecutionResponse::getJson() {
    FileLogger logger;

    logger.log("Starting parsing response into json ...");

    string r = "{";

    /* Print results */
    r.append("\"results\": [");
    bool firstRecord = true;
    for (auto res : this->results) {
        if (!firstRecord) r.append(",");
        firstRecord = false;
        r.append("[");
        bool firstCol = true;
        for (auto resCol : res) {
            if (!firstCol) r.append(",");
            firstCol = false;
            r.append("\"" + resCol + "\"");
        }
        r.append("]");
    }
    r.append("],");

    /* Print fields */
    r.append("\"fields\": [");
    bool first = true;
    for (auto f : this->fields) {
        if (!first) r.append(",");
        first = false;
        r.append("{");
        r.append("\"name\": \"" + f.name + "\"");
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
        r.append(",\"type\": \"" + d + "\"");
        r.append("}");
    }
    r.append("],");

    r.append("\"messages\": ");
    r.append("[");
    first = true;
    for (auto msg : this->messages) {
        if (!first) r.append(",");
        first = false;
        r.append("{");
        r.append("\"command\": ");
        r.append("\"" + msg.command + "\",");
        r.append("\"message\": ");
        r.append("\"" + msg.message + "\"");
        r.append("}");
    }
    r.append("],");

    /* Print error */
    r.append("\"error\": \"" + this->error + "\"");

    r.append("}");

    logger.log("JSON Response parsed successfully!");

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
