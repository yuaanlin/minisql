#include "API.h"
#include "BufferManager.h"
#include "Condition.h"
#include "Attribute.h"
#include "RecordManager.h"
#include "BufferManager.h"
#include <string>
#include <vector>

void BufferManager::initfile(FileNode& file) {
    file.name = "";
    file.prev = NULL;
    file.next = NULL;
    file.isPined = false;
}

void BufferManager::initblock(BlockNode& block) {
    block.isPined = false;
    block.isDirty = false;
    block.isBottom = true;
    block.prev = NULL;
    block.next = NULL;
    block.offset = -1;
    block.address = "";
}

void setDirty(BlockNode* block) { block->isDirty = true; }

void cleanDirty(BlockNode* block) { block->isDirty = false; }

void setPined(BlockNode* block) { block->isPined = true; }

FileNode* BufferManager::getFile(string fileName) {
    BlockNode* btmp = NULL;
    FileNode* ftmp = NULL;
    if (Filehead == NULL) return NULL;
    ftmp = filehead;
    for (; ftmp != NULL; ftmp = ftmp->next) {
        if (strcmp(fileName, ftmp->fileName)&& ftmp->isPined = false) {
            return ftmp;
        }
    }
    return NULL;
}

BlockNode* getBlockHead(string fileName) {
    FileNode* ftmp = getFile(fileName, false);
    return ftmp->blockHead;
}

BlockNode* BufferManager::getBlock(FileNode* file, int offset) {
    BlockNode* btmp = NULL;
    btmp = file->blockHead;
    if (offset > total_block) {
        return NULL;
    }
    if (btmp == NULL) return NULL;
    //遍历该file下所有block
    for (; btmp != NULL; btmp = btmp->next) {
        if (btmp->offset == offset && btmp->isPined == false) return btmp;
    }
    return NULL;
}

void BufferManager::connect(FileNode* file, BlockNode* block) {
    block->fileName = file->name;
    block->next = file->blockHead;
    file->blockHead = block;
}

BlockNode* BufferManager::getNextBlock(FileNode* fileNode, BlockNode* block) {
    if (block->next == NULL) return NULL;

    if (block->isBottom == false && block->isPined == false)  //不是bottom
    {
        return getBlock(fileNode, (block->offset)++, false);
    }

    else {
        BlockNode* btmp = NULL;
        block->next = btmp;
        block->isBottom = false;
        initblock(btmp);
        btmp->offset = (block->offset)++;
        return btmp;
    }
}

void BufferManager::deletefileNode(string fileName) {
    fileNode* ftmp = getFile(fileName);
    if (ftmp->prev == NULL)  // head
        ftmp->next->prev = NULL;
    else if (ftmp->next == NULL)  // tail
        ftmp->prev->next = NULL;
    else {
        ftmp->next->prev = ftmp->prev;
        ftmp->prev->next = ftmp->next;
    }
}

void BufferManager::writtenBackToDisk(const char* fileName, blockNode* block) {
    fileNode* ftmp = getFile(fileName);
    if (block->isDirty == false) return;
    FILE* fp = fopen(b.fileName.c_str(), "rb+");
    if (fp != NULL) {
        if(!(fseek(fp,block.offset,0))
        {
            fwrite(block->Data, 1, block.offset * total_bloc, fp);
        }
    }
    fclose(fp);
}