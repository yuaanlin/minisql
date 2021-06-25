#ifndef __minisql_interpreter_h__
#define __minisql_interpreter_h__

#include <string>
#include <vector>
#include "../FileLogger/FileLogger.h"
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
    FileLogger *logger;
    API *api;
    CatalogManager *catalogManager;

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
     * @param l Logger
     */
    void init(API *a, FileLogger *l, CatalogManager *c);

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
     * Check if current char is still a part of word.
     *
     * 检查当前字符是否仍然是一个单词的一部分，如果遇到不属于 a-z, A-Z, 0-9, _,
     * - 的其它字符将会返回 false，即该字符不是上一个单词的一部分
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
     * @param sql string
     * @param p *int
     */
    ExecutionResponse interpretSelectOperation(string sql, int *p);

    /**
     * There is no documention for this function yet.
     *
     * 该函数的文档尚未完善。
     *
     * @param sql string
     * @param p *int
     */
    ExecutionResponse interpretCreateTableOperation(string sql, int *p);

    /**
     * There is no documention for this function yet.
     *
     * 该函数的文档尚未完善。
     *
     * @param sql string
     * @param p *int
     */
    ExecutionResponse interpretCreateIndexOperation(string sql, int *p);

    /**
     * There is no documention for this function yet.
     *
     * 该函数的文档尚未完善。
     *
     * @param sql string
     * @param p *int
     */
    ExecutionResponse interpretDropTableOperation(string sql, int *p);

    /**
     * There is no documention for this function yet.
     *
     * 该函数的文档尚未完善。
     *
     * @param sql string
     * @param p *int
     */
    ExecutionResponse interpretDropIndexOperation(string sql, int *p);

    /**
     * There is no documention for this function yet.
     *
     * 该函数的文档尚未完善。
     *
     * @param sql string
     * @param p *int
     */
    ExecutionResponse interpretUpdateOperation(string sql, int *p);

    /**
     * There is no documention for this function yet.
     *
     * 该函数的文档尚未完善。
     *
     * @param sql string
     * @param p *int
     */
    ExecutionResponse interpretDeleteOperation(string sql, int *p);

    /**
     * There is no documention for this function yet.
     *
     * 该函数的文档尚未完善。
     *
     * @param sql string
     * @param p *int
     */
    ExecutionResponse interpretInsertOperation(string sql, int *p);
};

#endif