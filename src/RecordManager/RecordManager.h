#ifndef __minisql_record_manager__
#define __minisql_record_manager__

#include "../Condition/Condition.h"
class API;
class BufferManager;
class RecordManager {
   private:
    API *api;
    BufferManager *bufferManager;

   public:
    void init(API *a, BufferManager *b);

    // 功能：建立表文件
    void createTable(string table_name);

    // 功能：删除表文件
    void dropTable(string table_name);

    // 功能：更新文件
    void updateRecord(string tableName, vector<string> fields,
                      vector<string> values, vector<Condition> conditions);

    // 功能：向对应表中插入一条记录
    void insertRecord(string table_name, vector<string> record);

    // 功能：删除对应表中所有记录（不删除表文件）
    int deleteRecord(string table_name);

    // 功能：删除对应表中所有目标属性值满足 conditions 的记录
    int deleteRecord(string table_name, vector<Condition> conditions);

    // 功能：返回所有满足 conditions 的记录
    vector<vector<string>> selectRecord(string tableName,
                                        vector<Condition> conditions);

    // 功能：返回所有满足 conditions 的记录
    vector<vector<string>> selectRecordByOffset(string tableName,
                                                vector<Condition> conditions,
                                                int offset);

    // 功能：对表中已经存在的记录建立索引
    void indexRecords(string tableName, string attrName);
};

#endif