#ifndef __minisql_interpreter_h__
#define __minisql_interpreter_h__

#include <string>

class API;
class Interpreter {
   private:
    API *api;

   public:
    void execute(string sqlCommand);
    void init(API *a);
};

#endif