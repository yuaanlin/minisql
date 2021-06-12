#ifndef __minisql_interpreter_h__
#define __minisql_interpreter_h__

#include <string>
#include <vector>
#include "../Attribute/Attribute.h"

using namespace std;

class API;

class ExecutionResponse {
   public:
    vector<vector<string>> results;
    vector<Attribute> fields;
    string error;
    string getJson();
};

class Interpreter {
   private:
    API *api;

   public:
    ExecutionResponse execute(string sqlCommand);
    void init(API *a);
    string getWord(string s, int from);
    bool isSame(string a, string b);
};

#endif