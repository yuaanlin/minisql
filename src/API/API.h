#ifndef __minisql_api_h__
#define __minisql_api_h__

#include "../global.h"
#include "../CatalogManager/CatalogManager.h"
#include "../Condition/Condition.h"
// #include "../RecordManager/RecordManager.h"
#include "../IndexManager/IndexManager.h"
#include "../FakeRecordManager/FakeRecordManager.h"

#include <vector>
#include <string>

using namespace std;

class API {
   private:
    CatalogManager *catalogManager;
    FakeRecordManager *recordManager;
    IndexManager *indexManager;
    FileLogger *logger;

   public:
    /**
     *
     * 模块初始化
     *
     * @param c CatalogManager
     * @param r RecordManager
     * @param i IndexManager
     * @param l FileLogger
     */
    void init(CatalogManager *c, FakeRecordManager *r, IndexManager *ind,
              FileLogger *logger);

    /**
     *
     * 调用各个模块以进行 CREATE INDEX 操作
     *
     * @param indexName 索引名
     * @param tableName 表名
     * @param fields 要建立索引的栏位
     */
    void createIndex(string indexName, string tableName, vector<string> fields);

    /**
     *
     * 调用各个模块以进行 CREAT TABLE 操作
     *
     * @param tableName 表名
     * @param attrs 属性列表
     */
    void createTable(string tableName, vector<Attribute> attrs);

    /**
     *
     * 调用各个模块以进行 SELECT 操作
     *
     * @param tableName 表名
     * @param columns 栏位
     * @param conditions 筛选条件
     *
     * @return 查询结果
     */
    Records selectRecords(string tableName, vector<string> columns,
                          vector<Condition> conditions);

    /**
     *
     * 调用各个模块以进行 INSERT 操作
     *
     * @param tableName 表名
     * @param values 要插入的记录
     */
    void insertRecord(string tableName, vector<string> values);

    /**
     *
     * 调用各个模块以进行 UPDATE 操作
     *
     * @param tableName 表名
     * @param fields 要更改的栏位
     * @param values 要更改的值
     * @param condition 筛选条件
     *
     * @return 成功修改的记录数量
     */
    int updateRecord(string tableName, vector<string> fields,
                     vector<string> values, vector<Condition> conditions);

    /**
     *
     * 调用各个模块以进行 DELETE 操作
     *
     * @param tableName 表名
     * @param conditions 筛选条件
     *
     * @return 成功删除的记录数量
     */
    int deleteRecord(string tableName, vector<Condition> conditions);

    /**
     *
     * 调用各个模块以进行 DROP TABLE 操作
     *
     * @param sqlCommand 要删除的表名
     */
    void dropTable(string tableName);

    /**
     *
     * 调用各个模块以进行 DROP INDEX 操作
     *
     * @param indexName 要删除的索引名
     */
    void dropIndex(string indexName);
};

#endif