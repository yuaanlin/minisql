#include "Condition.h"

Condition::Condition(string a, char o, string v) {
    attributeName = a;
    operate = o;
    value = v;
}

Condition::Condition() {}

string Condition::toJson() {
    string r;
    r.append("{");
    r.append("\"attribute\": \"" + attributeName + "\"");
    string d;
    switch (operate) {
        case Condition::EQ_OPERATOR:
            d = "EQUAL";
            break;
        case Condition::LT_OPERATOR:
            d = "LESS_THAN";
            break;
        case Condition::BT_OPERATOR:
            d = "BIGGER_THAN";
            break;
        case Condition::LTE_OPERATOR:
            d = "LESS_THAN_OR_EQUAL";
            break;
        case Condition::BTE_OPERATOR:
            d = "BIGGER_THAN_OR_EQUAL";
            break;
        case Condition::NEQ_OPERATOR:
            d = "NOT_EQUAL";
            break;
    }
    r.append(",\"operation\": \"" + d + "\"");
    r.append(",\"value\": \"" + value + "\"");
    r.append("}");
    return r;
}