#ifndef __minisql_interpreter_h__
#define __minisql_interpreter_h__

#include <string>
#include <vector>
#include "../Attribute/Attribute.h"
#include "../API/API.h"
#include <fstream>

using namespace std;

class ExecutionResponse {
   public:
    Records results;
    vector<Attribute> fields;
    string error;
    string getJson();
};

class Interpreter {
   private:
    API *api;

   public:
    /**
     * There is no documention for this function yet.
     *
     * 该函数的文档尚未完善。
     *
     * @param sqlCommand string
     *
     * @return ExecutionResponse
     */
    ExecutionResponse execute(string sqlCommand);

    /**
     * There is no documention for this function yet.
     *
     * 该函数的文档尚未完善。
     *
     * @param a API
     */
    void init(API *a);

    /**
     * Read an word from the position of given string.
     *
     * 从给定的字符串中特定位置开始读取一个单词。
     *
     * @param s the given string
     * @param from the postion to start read
     *
     * @return The first word in string format from the given postion.
     *
     * @throws EOF_REACHED The end of given string reached.
     *
     */
    string getWord(string s, int *from);

    /**
     * There is no documention for this function yet.
     *
     * 该函数的文档尚未完善。
     *
     * @param c char
     *
     * @return bool
     */
    bool isLetter(char c);

    /**
     * There is no documention for this function yet.
     *
     * 该函数的文档尚未完善。
     *
     * @param a string
     * @param b string
     *
     * @return bool
     */
    bool isSame(string a, string b);

    /**
     * There is no documention for this function yet.
     *
     * 该函数的文档尚未完善。
     *
     * @param a string
     *
     * @return bool
     */
    bool isKeyword(string a);

    /**
     * There is no documention for this function yet.
     *
     * 该函数的文档尚未完善。
     *
     * @param s string
     */
    void log(string s);
};

#endif