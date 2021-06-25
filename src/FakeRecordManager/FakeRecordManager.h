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
    unordered_map<string, FakeTable> tables;
    void init(FileLogger *l, CatalogManager *c);
    void saveTablesToFiles();
    void readTablesFromFiles(vector<string> tableNames);
    Records selectRecord(string tableName, vector<Condition> conditions);
    void insertRecord(string table_name, vector<string> record);
    void createTable(string table_name);
    void dropTable(string table_name);
};

#endif