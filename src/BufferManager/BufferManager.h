#ifndef __minisql_buffer_manager_h__
#define __minisql_buffer_manager_h__

#include "../BlockNode/BlockNode.h"

class BufferManager {
   private:
   public:
    void init();
    // 功能：获取一个文件的第一个 block
    BlockNode* getBlockHead(string fileName);

    // 功能：获取一个 block 的下一个 block，如果已经最后了则开新 block
    BlockNode* getNextBlock(string fileName, BlockNode* block);

    // 功能：获取一个文件的第 offset 个 block
    BlockNode* getBlock(string filename, int offset);
};

#endif