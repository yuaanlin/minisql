#ifndef _index_manager_h__
#define _index_manager_h__

#include <stdio.h>
#include <string>

#include "../BPTree/BPTree.h"
#include "../FakeRecordManager/FakeRecordManager.h"

class IndexManager {
   private:
    FakeRecordManager* rm;

   public:
    enum IndexManagerError {
        INSRET_INDEX_ERROR,
        DROP_INDEX_ERROR,
        DELETE_INDEX_ERROR,
        SEARCH_INDEX_ERROR,
        SEARCH_RANGE_ERROR
    };

    void init(FakeRecordManager* r);

    void createIndex(string indexName,
                     DataType type);  //功能：创建索引文件及B+树

    void dropIndex(string indexName);  //功能：删除索引、B+树及文件

    void insertIndex(string indexName, string key,
                     int offset);  //功能：在指定索引中插入一个key

    void deleteIndex(string indexName,
                     string key);  // 功能：在索引中删除相应的 Key

    vector<int> searchRange(string indexName, string data1,
                            string data2);  //功能：范围查找

    int search(string indexName, string key);  //功能：根据 key 查找

    void CreateOne(Index indexs, int attrindex);

    int string_int(string key);      //类型转换
    float string_float(string key);  //类型转换
};

struct Trees {
    DataType type;
    string IN;  // IN = indexname
    BPTree_int* T_i;
    BPTree_float* T_f;
    BPTree_string* T_s;
};
typedef struct Trees trees;
#endif