#ifndef __minisql_table_h__
#define __minisql_table_h__

#include "../Attribute/Attribute.h"
#include <string>
#include <vector>

class Table {
   public:
    string name;
    vector<Attribute> attributes;

    /**
     * There is no documention for this function yet.
     *
     * 该函数的文档尚未完善。
     *
     * @param sqlCommand string
     *
     * @return ExecutionResponse
     */
    Table();

    /**
     * There is no documention for this function yet.
     *
     * 该函数的文档尚未完善。
     *
     * @param sqlCommand string
     *
     * @return ExecutionResponse
     */
    Table(string name, vector<Attribute> attributes);
};

#endif