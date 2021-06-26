#ifndef __minisql_interpreter_h__
#define __minisql_interpreter_h__

#include <string>
#include <vector>
#include "../FileLogger/FileLogger.h"
#include "../Attribute/Attribute.h"
#include "../API/API.h"
#include <fstream>

using namespace std;

class ExecutionMessage {
   public:
    string command;
    string message;
};

class OneCommandExecutionResponse {
   public:
    Records results;
    vector<Attribute> fields;
    string cmd;
    string msg;
};

class ExecutionResponse {
   public:
    Records results;
    vector<Attribute> fields;
    vector<ExecutionMessage> messages;
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
     *
     * 执行传入的 SQL 语句
     *
     * @param sqlCommand string
     *
     * @return OneCommandExecutionResponse
     */
    OneCommandExecutionResponse execute(string sqlCommand);

    /**
     *
     * 模块初始化
     *
     * @param a API
     * @param l FileLogger
     * @param c CatalogManager
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
     *
     * 模糊判断两字串是否相等，不区分大小写
     *
     * @param a string
     * @param b string
     *
     * @return bool
     */
    bool isSame(string a, string b);

    /**
     *
     * 判断传入的字串是否为 SQL 的关键字
     *
     * @param a string
     *
     * @return bool
     */
    bool isKeyword(string a);

    /**
     *
     * 抽象化 SELECT 操作的运行过程
     *
     * @param sql string
     * @param p *int
     *
     * @
     */
    OneCommandExecutionResponse interpretSelectOperation(string sql, int *p);

    /**
     * 抽象化 CREATE TABLE 操作的运行流程
     *
     * @param sql string
     * @param p *int
     */
    OneCommandExecutionResponse interpretCreateTableOperation(string sql,
                                                              int *p);

    /**
     *
     * 抽象化 CREATE INDEX 操作的运行流程
     *
     * @param sql string
     * @param p *int
     */
    OneCommandExecutionResponse interpretCreateIndexOperation(string sql,
                                                              int *p);

    /**
     *
     * 抽象化 DROP TABLE 操作的运行流程
     *
     * @param sql string
     * @param p *int
     */
    OneCommandExecutionResponse interpretDropTableOperation(string sql, int *p);

    /**
     *
     * 抽象化 DROP INDEX 操作的运行流程
     *
     * @param sql string
     * @param p *int
     */
    OneCommandExecutionResponse interpretDropIndexOperation(string sql, int *p);

    /**
     *
     * 抽象化 UPDATE 操作的运行流程
     *
     * @param sql string
     * @param p *int
     */
    OneCommandExecutionResponse interpretUpdateOperation(string sql, int *p);

    /**
     *
     * 抽象化 DELETE 操作的运行流程
     *
     * @param sql string
     * @param p *int
     */
    OneCommandExecutionResponse interpretDeleteOperation(string sql, int *p);

    /**
     *
     * 抽象化 INSERT 操作的运行流程
     *
     * @param sql string
     * @param p *int
     */
    OneCommandExecutionResponse interpretInsertOperation(string sql, int *p);
};

#endif