#include "Table.h"

using namespace std;

Table::Table() {}

Table::Table(string tableName, vector<Attribute> attributes) {
    this->name = tableName;
    this->attributes = attributes;
}