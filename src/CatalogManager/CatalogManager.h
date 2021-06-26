#ifndef __catalog_manager_h__
#define __catalog_manager_h__

#include <string>
#include <vector>
#include <unordered_map>
#include "../Attribute/Attribute.h"
#include "../Table/Table.h"
#include "../Index/Index.h"
#include "../FileLogger/FileLogger.h"

using namespace std;

class CatalogManager {
   private:
    FileLogger *logger;

   public:
    enum CatalogManagerError { ATTRIBUTE_NOT_FOUND };

    unordered_map<string, Table> tables;
    unordered_map<string, Index> indexes;

    /**
     *
     * 模块初始化
     *
     * @param l FileLogger
     */
    void init(FileLogger *l);

    /**
     *
     * 创建数据表元数据
     *
     * @param table 要创建的数据表
     */
    void createTable(Table table);

    /**
     *
     * 根据索引名查询表是否存在
     *
     * @param tableName 索引名
     *
     * @return 表是否存在
     */
    bool isTableExist(string tableName);

    /**
     *
     * 从 metadata 文件目录载入数据表元数据
     *
     */
    void readTableFiles();

    /**
     *
     * 删除数据表
     *
     * @param tableName 要删除的表名
     */
    void dropTable(string tableName);

    /**
     *
     * 建立索引元数据
     *
     * @param index 要建立的索引
     */
    void createIndex(Index index);

    /**
     *
     * 根据索引名查询索引是否存在
     *
     * @param indexName 索引名
     *
     * @return 索引是否存在
     */
    bool isIndexExist(string indexName);

    /**
     *
     * 从 metadata 文件目录载入所有索引
     *
     */
    void readIndexFiles();

    /**
     *
     * 删除索引
     *
     * @param indexName 索引名
     */
    void dropIndex(string indexName);

    /**
     *
     * 获取某数据表的元数据
     *
     * @param tableName 表名
     *
     * @return 数据表的元数据
     */
    Table getTable(string tableName);

    /**
     *
     * 获取所有数据表的元数据
     *
     * @return 所有数据表的元数据
     */
    vector<Table> getTables();

    /**
     *
     * 根据索引名查询索引的元数据
     *
     * @param indexName 索引名称
     *
     * @return 索引的元数据
     */
    Index getIndex(string indexName);

    /**
     *
     * 查询某数据表的某栏位的数据类型
     *
     * @param tableName 表名
     * @param fieldName 属性名
     *
     * @return 数据类型
     */
    DataType getDataTypeOfAttribute(string tableName, string fieldName);

    Index *getIndex(string tableName, string fieldName);
};

#endif