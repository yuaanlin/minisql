#ifndef BPTREE_H_
#define BPTREE_H_

#include <stdio.h>
#include <string>
#include <vector>

#include "../Index/Index.h"

class BPTreeNode_int {
   private:
    int degree;  //度，相当于'容量'
   public:
    bool isleaf;
    bool isroot;
    int KeyNum;                    //节点内键的数量,相当于'余量'
    BPTreeNode_int* NextLeafNode;  //叶子节点间的指针
    vector<int> KeyArray;
    vector<int> ValArray;
    vector<BPTreeNode_int*> children;
    BPTreeNode_int* parent;

    BPTreeNode_int(int degree,
                   bool LeafNode = false);  //创建节点。缺省自动建非叶节点

    bool searchkey_node(int key, int& index);
    int AddToBranch(int& key);
    int AddToLeaf(int& key, int val);
    BPTreeNode_int* splite(int& key);
    bool deletekey(int index);
};

class BPTree_int {
   private:
    string FileName;
    BPTreeNode_int* pLeftLeaf;
    int KeySize;
    int height;
    int KeyNum;
    int NodeNum;
    int degree;
    bool trim(BPTreeNode_int* node);
    bool maintain(BPTreeNode_int* node);
    void InitTree();

   public:
    BPTreeNode_int* pRoot;
    BPTree_int(string name, int KeySize, int degree);
    ~BPTree_int();

    BPTreeNode_int* searchkey_tree(int key, BPTreeNode_int* node);
    bool InsertKey(int& key, int val);
    bool DeleteKey(int& key);
    void DropTree(BPTreeNode_int* node);
    BPTreeNode_int* findmin(BPTreeNode_int* node);
    friend class BPTreeNode_int;
};

class BPTreeNode_float {
   private:
    int degree;  //度，相当于'容量'
   public:
    bool isleaf;
    bool isroot;
    int KeyNum;                      //节点内键的数量,相当于'余量'
    BPTreeNode_float* NextLeafNode;  //叶子节点间的指针
    vector<float> KeyArray;
    vector<int> ValArray;
    vector<BPTreeNode_float*> children;
    BPTreeNode_float* parent;

    BPTreeNode_float(int degree,
                     bool LeafNode = false);  //创建节点。缺省自动建非叶节点

    bool searchkey_node(float key, int& index);
    int AddToBranch(float& key);
    int AddToLeaf(float& key, int val);
    BPTreeNode_float* splite(float& key);
    bool deletekey(int index);
};

class BPTree_float {
   private:
    string FileName;
    BPTreeNode_float* pLeftLeaf;
    int KeySize;
    int height;
    int KeyNum;
    int NodeNum;
    int degree;
    bool trim(BPTreeNode_float* node);
    bool maintain(BPTreeNode_float* node);
    void InitTree();

   public:
    BPTreeNode_float* pRoot;
    BPTree_float(string name, int KeySize, int degree);
    ~BPTree_float();

    BPTreeNode_float* searchkey_tree(float key, BPTreeNode_float* node);
    bool InsertKey(float& key, int val);
    bool DeleteKey(float& key);
    void DropTree(BPTreeNode_float* node);
    BPTreeNode_float* findmin(BPTreeNode_float* node);
    friend class BPTreeNode_float;
};

class BPTreeNode_string {
   private:
    int degree;  //度，相当于'容量'
   public:
    bool isleaf;
    bool isroot;
    int KeyNum;                       //节点内键的数量,相当于'余量'
    BPTreeNode_string* NextLeafNode;  //叶子节点间的指针
    vector<string> KeyArray;
    vector<int> ValArray;
    vector<BPTreeNode_string*> children;
    BPTreeNode_string* parent;

    BPTreeNode_string(int degree,
                      bool LeafNode = false);  //创建节点。缺省自动建非叶节点

    bool searchkey_node(string key, int& index);
    int AddToBranch(string& key);
    int AddToLeaf(string& key, int val);
    BPTreeNode_string* splite(string& key);
    bool deletekey(int index);
};

class BPTree_string {
   private:
    string FileName;
    BPTreeNode_string* pLeftLeaf;
    int KeySize;
    int height;
    int KeyNum;
    int NodeNum;
    int degree;
    bool trim(BPTreeNode_string* node);
    bool maintain(BPTreeNode_string* node);
    void InitTree();

   public:
    BPTreeNode_string* pRoot;
    BPTree_string(string name, int KeySize, int degree);
    ~BPTree_string();

    BPTreeNode_string* searchkey_tree(string key, BPTreeNode_string* node);
    bool InsertKey(string& key, int val);
    bool DeleteKey(string& key);
    void DropTree(BPTreeNode_string* node);
    void WriteData();
    BPTreeNode_string* findmin(BPTreeNode_string* node);
    friend class BPTreeNode_string;
};

#endif
