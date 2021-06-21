#ifndef __minisql_record_manager__
#define __minisql_record_manager__

#include "../API/API.h"
#include "../BufferManager/BufferManager.h"
#include "../Condition/Condition.h"
#include "../Attribute/Attribute.h"
#include "../RecordManager/RecordManager.h"
#include "../BlockNode/BlockNode.h"
#include "../BufferManager/BufferManager.h"
#include <string>
#include <vector>

using namespace std;

class RecordManager {
   public:
    RecordManager() {}
    API *api;
    BufferManager *bufferManager;

    void init(API *a, BufferManager *b);

    void createTable(string table_name);
    //功能：建立表文件

    void dropTable(string table_name);
    //功能：删除表文件

    void createIndex(string index_name);
    //功能：建立目录

    void dropIndex(string index_name);
    //功能：删除目录

    int insertRecord(string table_name, vector<string> record);
    //功能：向对应表中插入一条记录

    int deleteRecord(string table_name);
    //功能：删除对应表中所有记录（不删除表文件）

    int deleteRecordconditional(string table_name,
                                vector<Condition> conditions);
    //功能：删除对应表中所有目标属性值满足 conditions 的记录

    int selectRecord(string table_name, vector<Condition> conditions);
    //功能：返回所有满足 conditions 的记录

    void indexRecords(string table_name, string index_name);
    //功能：对表中已经存在的记录建立索引

    // int recordBlockShow(string table_name, vector<string> attributeName,
    // vector<Condition> conditions, int blockOffset);

    int indexRecordBlockAlreadyInsert(string tableName, string indexName,
                                      BlockNode *block);

    string Gettablefilename(string table_name);

    string Getindexfilename(string index_name);
};

#endif