#ifndef __minisql_fake_record_manager__
#define __minisql_fake_record_manager__

class API;
class BufferManager;

#include "../Condition/Condition.h"
#include "../FileLogger/FileLogger.h"
#include "../CatalogManager/CatalogManager.h"
#include "../global.h"
#include <unordered_map>

/**
 *  A FakeRecordBlock means a part of data in table.
 *  This is used to simulate buffer for testing IndexManager.
 *
 * 一个 FakeRecordBlock 代表一张数据表中部分的数据，
 * 这是用于在没有 BufferManager 的情况下测试 IndexManager 是否正常运行
 */
typedef Records FakeRecordBlock;

/**
 * A FakeTable is a vector<FakeRecordBlock>
 * This is used to simulate RecordManager.
 *
 * 一个 FakeTable 是多个 FakeRecordBlock 组成的 vector
 * 这是用于在没有 RecordManager 的情况下测试其他模块是否正常运行。
 */
typedef vector<FakeRecordBlock> FakeTable;

class FakeRecordManager {
   private:
    CatalogManager *catalogManager;
    FileLogger *logger;

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
    unordered_map<string, FakeTable> tables;

    /**
     * There is no documention for this function yet.
     *
     * 该函数的文档尚未完善。
     *
     * @param sqlCommand string
     *
     * @return ExecutionResponse
     */
    void init(FileLogger *l, CatalogManager *c);

    /**
     * There is no documention for this function yet.
     *
     * 该函数的文档尚未完善。
     *
     * @param sqlCommand string
     *
     * @return ExecutionResponse
     */
    void saveTablesToFiles();

    /**
     * There is no documention for this function yet.
     *
     * 该函数的文档尚未完善。
     *
     * @param sqlCommand string
     *
     * @return ExecutionResponse
     */
    void readTablesFromFiles(vector<string> tableNames);

    /**
     * There is no documention for this function yet.
     *
     * 该函数的文档尚未完善。
     *
     * @param sqlCommand string
     *
     * @return ExecutionResponse
     */
    Records selectRecord(string tableName, vector<Condition> conditions);

    /**
     * There is no documention for this function yet.
     *
     * 该函数的文档尚未完善。
     *
     * @param sqlCommand string
     *
     * @return ExecutionResponse
     */
    void insertRecord(string table_name, vector<string> record);

    /**
     * There is no documention for this function yet.
     *
     * 该函数的文档尚未完善。
     *
     * @param sqlCommand string
     *
     * @return ExecutionResponse
     */
    void createTable(string table_name);

    /**
     * There is no documention for this function yet.
     *
     * 该函数的文档尚未完善。
     *
     * @param sqlCommand string
     *
     * @return ExecutionResponse
     */
    void dropTable(string table_name);

    /**
     * There is no documention for this function yet.
     *
     * 该函数的文档尚未完善。
     *
     * @param sqlCommand string
     *
     * @return ExecutionResponse
     */
    int updateRecord(string tableName, vector<string> fields,
                     vector<string> values, vector<Condition> conditions);

    /**
     * There is no documention for this function yet.
     *
     * 该函数的文档尚未完善。
     *
     * @param sqlCommand string
     *
     * @return ExecutionResponse
     */
    int deleteRecord(string tableName, vector<Condition> conditions);

    /**
     * There is no documention for this function yet.
     *
     * 该函数的文档尚未完善。
     *
     * @param sqlCommand string
     *
     * @return ExecutionResponse
     */
    static vector<int> getAttrIndex(vector<Attribute> attributes,
                                    vector<Condition> find);

    /**
     * There is no documention for this function yet.
     *
     * 该函数的文档尚未完善。
     *
     * @param sqlCommand string
     *
     * @return ExecutionResponse
     */
    static vector<int> getAttrIndex(vector<Attribute> attributes,
                                    vector<string> find);

    /**
     * There is no documention for this function yet.
     *
     * 该函数的文档尚未完善。
     *
     * @param sqlCommand string
     *
     * @return ExecutionResponse
     */
    static bool isMatchConditions(vector<string> record,
                                  vector<int> conditionAttrIndex,
                                  vector<Condition> conditions);
};

#endif