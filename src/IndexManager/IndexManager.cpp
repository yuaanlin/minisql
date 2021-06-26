#include <sstream>

#include "../IndexManager/IndexManager.h"
#include "../BPTree/BPTree.h"
#include "../global.h"

static int n = 0;
static trees AT[100];  // AT means all trees

void IndexManager::init() {
    for (int i = 0; i < 100; i++) {
        AT[i].T_i = NULL;
        AT[i].T_f = NULL;
        AT[i].T_s = NULL;
        AT[i].IN = string();
        AT[i].type = Integer;
    }
}

void IndexManager::createIndex(string indexName, DataType type) {
    AT[n].IN = indexName;
    if (type == 0) {  // int
        int degree = 7;
        BPTree_int* T = new BPTree_int(indexName, sizeof(int), degree);
        AT[n].T_i = T;
        AT[n].type = Integer;
        delete T;
    } else if (type == 1) {  // float
        int degree = 7;
        BPTree_float* T = new BPTree_float(indexName, sizeof(float), degree);
        AT[n].T_f = T;
        AT[n].type = Float;
        delete T;
    } else {  // string
        int degree = 7;
        BPTree_string* T = new BPTree_string(indexName, sizeof(string),
                                             degree);  // sizeofstring??
        AT[n].T_s = T;
        AT[n].type = String;
        delete T;
    }
    n++;
}

void IndexManager::dropIndex(string indexName) {
    int flag = 0;
    for (int i = 0; i < 100; i++) {
        if (AT[i].IN == indexName) {
            flag = 1;
            switch (AT[i].type) {
                case Integer:
                    delete AT[i].T_i;
                    AT[i].T_i = NULL;
                    for (int j = i; j < 99; j++) AT[j] = AT[j + 1];
                    break;
                case Float:
                    delete AT[i].T_f;
                    AT[i].T_f = NULL;
                    for (int j = i; j < 99; j++) AT[j] = AT[j + 1];
                    break;
                case String:
                    delete AT[i].T_s;
                    AT[i].T_s = NULL;
                    for (int j = i; j < 99; j++) AT[j] = AT[j + 1];
                    break;
            }
            break;
        } else
            continue;
    }
    if (!flag)
        throw DROP_INDEX_ERROR;
    else
        n--;
}

int IndexManager::string_int(string key) {
    stringstream ss;
    ss << key;
    int result;
    ss >> result;
    return result;
}

float IndexManager::string_float(string key) {
    stringstream ss;
    ss << key;
    float result;
    ss >> result;
    return result;
}

void IndexManager::insertIndex(string indexName, string key, int offset) {
    int flag = 0;
    for (int i = 0; i < 100; i++) {
        if (AT[i].IN == indexName) {
            flag = 1;
            int k1 = string_int(key);
            float k2 = string_float(key);
            switch (AT[i].type) {
                case Integer:
                    if (!AT[i].T_i->InsertKey(k1, offset))
                        throw INSRET_INDEX_ERROR;
                    break;
                case Float:
                    if (!AT[i].T_f->InsertKey(k2, offset))
                        throw INSRET_INDEX_ERROR;
                    break;
                case String:
                    if (!AT[i].T_s->InsertKey(key, offset))
                        throw INSRET_INDEX_ERROR;
                    break;
            }
            break;
        } else
            continue;
    }
    if (!flag) throw INSRET_INDEX_ERROR;
}

void IndexManager::deleteIndex(string indexName, string key) {
    int flag = 0;
    for (int i = 0; i < 100; i++) {
        if (AT[i].IN == indexName) {
            flag = 1;
            switch (AT[i].type) {
                case Integer:
                    int k1 = string_int(key);
                    if (!AT[i].T_i->DeleteKey(k1)) throw DELETE_INDEX_ERROR;
                    break;
                case Float:
                    float k2 = string_float(key);
                    if (!AT[i].T_f->DeleteKey(k2)) throw DELETE_INDEX_ERROR;
                    break;
                case String:
                    if (!AT[i].T_s->DeleteKey(key)) throw DELETE_INDEX_ERROR;
                    break;
            }
            break;
        } else
            continue;
    }
    if (!flag) throw DELETE_INDEX_ERROR;
}

int IndexManager::search(string indexName, string key) {
    int flag = 0;
    int index = 0;
    for (int i = 0; i < 100; i++) {
        if (AT[i].IN == indexName) {
            flag = 1;
            switch (AT[i].type) {
                case Integer:
                    int k1 = string_int(key);
                    BPTreeNode_int* TN1 =
                        AT[i].T_i->searchkey_tree(k1, AT[i].T_i->pRoot);
                    if (!TN1->searchkey_node(k1, index)) {
                        throw SEARCH_INDEX_ERROR;
                        return -1;
                    } else
                        return TN1->ValArray[index];
                    break;
                case Float:
                    float k2 = string_float(key);
                    BPTreeNode_float* TN2 =
                        AT[i].T_f->searchkey_tree(k2, AT[i].T_f->pRoot);
                    if (!TN2->searchkey_node(k2, index)) {
                        throw SEARCH_INDEX_ERROR;
                        return -1;
                    } else
                        return TN2->ValArray[index];
                    break;
                case String:
                    BPTreeNode_string* TN3 =
                        AT[i].T_s->searchkey_tree(key, AT[i].T_s->pRoot);
                    if (!TN3->searchkey_node(key, index)) {
                        throw SEARCH_INDEX_ERROR;
                        return -1;
                    } else
                        return TN3->ValArray[index];
                    break;
            }
            break;
        } else
            continue;
    }
    if (!flag) {
        throw SEARCH_INDEX_ERROR;
        return -1;
    }
}

vector<int> IndexManager::searchRange(string indexName, string data1,
                                      string data2) {
    vector<int> result;
    int index = 0;
    int flag = 0;
    for (int i = 0; i < 100; i++) {
        if (AT[i].IN == indexName) {
            flag = 1;
            switch (AT[i].type) {
                case Integer: {
                    int L1 = string_int(data1);
                    int R1 = string_int(data2);
                    int key1 = L1;
                    BPTreeNode_int* TN1 =
                        AT[i].T_i->searchkey_tree(key1, AT[i].T_i->pRoot);
                    if (!TN1->searchkey_node(key1, index))
                        throw SEARCH_RANGE_ERROR;
                    else {
                        while (key1 != R1) {
                            result.push_back(TN1->ValArray[index]);
                            if (index == TN1->KeyNum - 1) {
                                TN1 = TN1->NextLeafNode;
                                index = 0;
                                key1 = TN1->KeyArray[index];
                            } else {
                                index++;
                                key1 = TN1->KeyArray[index];
                            }
                        }
                        result.push_back(search(indexName, data2));
                    }
                    break;
                }
                case Float: {
                    float L2 = string_float(data1);
                    float R2 = string_float(data2);
                    float key2 = L2;
                    BPTreeNode_float* TN2 =
                        AT[i].T_f->searchkey_tree(key2, AT[i].T_f->pRoot);
                    if (!TN2->searchkey_node(key2, index))
                        throw SEARCH_RANGE_ERROR;
                    else {
                        while (key2 != R2) {
                            result.push_back(TN2->ValArray[index]);
                            if (index == TN2->KeyNum - 1) {
                                TN2 = TN2->NextLeafNode;
                                index = 0;
                                key2 = TN2->KeyArray[index];
                            } else {
                                index++;
                                key2 = TN2->KeyArray[index];
                            }
                        }
                        result.push_back(search(indexName, data2));
                    }
                    break;
                }
                case String:
                    string L3 = data1;
                    string R3 = data2;
                    string key3 = L3;
                    BPTreeNode_string* TN3 =
                        AT[i].T_s->searchkey_tree(key3, AT[i].T_s->pRoot);
                    if (!TN3->searchkey_node(key3, index))
                        throw SEARCH_RANGE_ERROR;
                    else {
                        while (key3 != R3) {
                            result.push_back(TN3->ValArray[index]);
                            if (index == TN3->KeyNum - 1) {
                                TN3 = TN3->NextLeafNode;
                                index = 0;
                                key3 = TN3->KeyArray[index];
                            } else {
                                index++;
                                key3 = TN3->KeyArray[index];
                            }
                        }
                        result.push_back(search(indexName, data2));
                    }
                    break;
            }
            break;
        } else
            continue;
    }
    if (!flag) throw SEARCH_RANGE_ERROR;
    return result;
}

void IndexManager::CreateOne(Index index, int attrindex) {
    string IN = index.indexName;
    FakeTable record = rm.tables[index.tableName];
    for (int i = 0; i < record.size(); i++) {
        for (int j = 0; j < record[i].size(); j++) {
            createIndex(IN, index.dataType);
            string key = record[i][j][attrindex];
            insertIndex(IN, key, i);
        }
    }
}
