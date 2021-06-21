#ifndef __minisql_buffer_manager_h__
#define __minisql_buffer_manager_h__

class BufferManager {
   private:
    FileNode *fileHead;
    FileNode file_pool[100];
    BlockNode block_pool[1000];
    int total_block;
    int total_file;

   public:
    void initfile(FileNode &file);
    void initblock(BlockNode &block);

    BufferManager();
    ~BufferManager();

    BlockNode *getBlockHead(FileNode *fileNode);
    //功能：获取一个文件的第一个 block

    BlockNode *getNextBlock(string *fileNode, BlockNode *block);
    //功能：获取一个 block 的下一个 block，如果已经最后了则开新 block

    BlockNode *getBlock(FileNode *file, int offset);
    //功能：获取某个文件的第 offset 个 block

    FileNode *getFile(string fileName);

    void connect(FileNode *file, BlockNode *block);

    //把block连接到file下
    void setDirty(BlockNode *block);

    //功能：标记对应的 block 被修改
    void cleanDirty(BlockNode *block);

    void setPined(BlockNode *block);
    //功能：标记对应的 block 锁住

    void deletefileNode(string fileName);

    void writtenBackToDisk(string fileName, BlockNode *block);
};

#endif