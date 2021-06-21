#ifndef __minisql_api_h__
#define __minisql_api_h__

#include "../global.h"
#include "../CatalogManager/CatalogManager.h"
#include "../Condition/Condition.h"
#include "../RecordManager/RecordManager.h"
#include "../IndexManager/IndexManager.h"

#include <vector>
#include <string>

using namespace std;

class API {
   private:
    CatalogManager *catalogManager;
    RecordManager *recordManager;
    IndexManager *indexManager;
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
    void init(CatalogManager *c, RecordManager *r, IndexManager *ind,
              FileLogger *logger);

    /**
     * There is no documention for this function yet.
     *
     * 该函数的文档尚未完善。
     *
     * @param sqlCommand string
     *
     * @return ExecutionResponse
     */
    void createIndex(string indexName, string tableName, vector<string> fields);

    /**
     * There is no documention for this function yet.
     *
     * 该函数的文档尚未完善。
     *
     * @param sqlCommand string
     *
     * @return ExecutionResponse
     */
    void createTable(string tableName, vector<Attribute> attrs);

    /**
     * There is no documention for this function yet.
     *
     * 该函数的文档尚未完善。
     *
     * @param sqlCommand string
     *
     * @return Records
     */
    Records selectRecords(string tableName, vector<string> columns,
                          vector<Condition> conditions);

    /**
     * There is no documention for this function yet.
     *
     * 该函数的文档尚未完善。
     *
     * @param sqlCommand string
     *
     * @return ExecutionResponse
     */
    void insertRecord(string tableName, vector<string> values);

    /**
     * There is no documention for this function yet.
     *
     * 该函数的文档尚未完善。
     *
     * @param sqlCommand string
     *
     * @return ExecutionResponse
     */
    void updateRecord();

    /**
     * There is no documention for this function yet.
     *
     * 该函数的文档尚未完善。
     *
     * @param sqlCommand string
     *
     * @return ExecutionResponse
     */
    void deleteRecord();
};

#endif