#ifndef __catalog_manager_h__
#define __catalog_manager_h__

#include <string>
#include <vector>
#include <unordered_map>
#include "../Attribute/Attribute.h"
#include "../Table/Table.h"
#include "../FileLogger/FileLogger.h"

using namespace std;

class API;
class BufferManager;

class CatalogManager {
   private:
    API *api;
    FileLogger *logger;

   public:
    unordered_map<string, Table> tables;

    /**
     * There is no documention for this function yet.
     *
     * 该函数的文档尚未完善。
     *
     * @param sqlCommand string
     *
     * @return ExecutionResponse
     */
    void init(API *a, FileLogger *l);

    /**
     * There is no documention for this function yet.
     *
     * 该函数的文档尚未完善。
     *
     * @param sqlCommand string
     *
     * @return ExecutionResponse
     */
    void createTable(Table table);

    /**
     * There is no documention for this function yet.
     *
     * 该函数的文档尚未完善。
     *
     * @param sqlCommand string
     *
     * @return ExecutionResponse
     */
    bool isTableExist(string tableName);

    /**
     * There is no documention for this function yet.
     *
     * 该函数的文档尚未完善。
     *
     * @param sqlCommand string
     *
     * @return ExecutionResponse
     */
    void readTableFiles();
};

#endif