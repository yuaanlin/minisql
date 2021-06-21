#ifndef __minisql_block_node_h__
#define __minisql_block_node_h__

#include <string>

using namespace std;

class BlockNode {
   public:
    string fileName;
    int offset;
    bool isPined;
    bool isDirty;
    bool isBottom;
    char* address;
    BlockNode* prev;
    BlockNode* next;
};

struct FileNode {
    string name;
    bool isPined;
    BlockNode* blockHead;
    FileNode* prev;
    FileNode* next;
};

#endif