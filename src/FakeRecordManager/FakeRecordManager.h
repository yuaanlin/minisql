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

    /**
     *
     * 模块初始化
     *
     * @param l FileLogger
     * @param c CatalogerManager
     */
    void init(FileLogger *l, CatalogManager *c);

    /**
     *
     * 将所有数据表的所有数据存入 .db 文件
     *
     */
    void saveTablesToFiles();

    /**
     *
     * 从 .db 文件载入所有记录
     *
     * @param tableNames 需要载入的表名
     */
    void readTablesFromFiles(vector<string> tableNames);

    /**
     *
     * 查询数据表中满足条件的记录
     *
     * @param tableName 表名
     * @param conditions 筛选条件列表
     *
     * @return 所有符合筛选条件的记录
     */
    Records selectRecord(string tableName, vector<Condition> conditions);

    /**
     *
     * 插入新记录到数据表
     *
     * @param tableName 表名
     * @param record 新纪录
     */
    void insertRecord(string tableName, vector<string> record);

    /**
     *
     * 建立数据表文件
     *
     * @param tableName 表名
     */
    void createTable(string tableName);

    /**
     *
     * 删除数据表文件
     *
     * @param tablename 表名
     */
    void dropTable(string tableName);

    /**
     *
     * 修改满足条件的记录
     *
     * @param tableName 表名
     * @param fields 要修改的栏位列表
     * @param values 各个栏位对应的新数据
     * @param conditions 筛选条件列表
     *
     * @return 成功修改的记录数量
     */
    int updateRecord(string tableName, vector<string> fields,
                     vector<string> values, vector<Condition> conditions);

    /**
     *
     * 删除满足筛选条件的数据
     *
     * @param tableName 表名
     * @param codintions 筛选条件
     *
     * @return 成功删除的记录数量
     */
    int deleteRecord(string tableName, vector<Condition> conditions);

    /**
     *
     * 将给定的多个筛选条件的栏位名转换为对应的下标
     *
     * @param attributes 数据表的属性列表
     * @param find 筛选条件列表
     *
     * @return 转换后的下标向量
     */
    static vector<int> getAttrIndex(vector<Attribute> attributes,
                                    vector<Condition> find);

    /**
     *
     * 将给定的多个栏位名转换为对应的下标
     *
     * @param attributes 数据表的属性列表
     * @param find 要转换成下标的栏位名列表
     *
     * @return 转换后的下标
     */
    static vector<int> getAttrIndex(vector<Attribute> attributes,
                                    vector<string> find);

    /**
     *
     * 检查一笔记录是否同时满足所有给定的筛选条件
     *
     * @param record 记录
     * @param conditionAttrIndex 筛选条件的栏位标记，可透过 getAttrIndex 获取
     * @param conditions 筛选条件列表
     *
     * @return 是否满足
     */
    static bool isMatchConditions(vector<string> record,
                                  vector<int> conditionAttrIndex,
                                  vector<Condition> conditions);
};

#endif