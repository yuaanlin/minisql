#include "RecordManager.h"
#include <string>

string RecordManager::Getindexfilename(string index_name) {
    string tmp = "";
    return "INDEX_FILE_" + index_name;
}

string RecordManager::Gettablefilename(string table_name) {
    string tmp = "";
    return tmp + "TABLE_FILE_" + table_name;
}

void RecordManager::createTable(string table_name) {
    table_name = "TABLE_FILE_" + table_name;
    FILE *fp = fopen(table_name.c_str(), "w+");
    fclose(fp);
}

void RecordManager::dropTable(string table_name) {
    table_name = Gettablefilename(table_name);
    bufferManager->delete_fileNode(table_name.c_str());
    remove(tableFileName.c_str());
}

void RecordManager::createIndex(string index_name) {
    index_name = Getindexfilename(index_name);
    FILE *fp = fopen(index_name.c_str(), "w+");
    fclose(fp);
}

void RecordManager::dropIndex(string index_name) {
    index_name = Getindexfilename(index_name);
    bufferManager->delete_fileNode(index_name.c_str());
    remove(index_name.c_str());
}

int RecordManager::insertRecord(string table_name, vector<string> record) {
    FileNode *ftmp =
        bufferManager->getFile(tableFileNameGet(table_name).c_str());
    BlockNode *btmp = bufferManager->getBlockHead(ftmp);

    if (btmp == NULL) return -1;

    while (btmp != NULL) {
        if (bufferManager->get_usingSize(*btmp) + sizeof(record) <=
            bufferManager->getBlockSize()) {
            char *addressBegin;
            addressBegin = bufferManager->get_content(*btmp) +
                           bufferManager->get_usingSize(*btmp);
            memcpy(addressBegin, record, sizeof(record));
            bufferManager->set_usingSize(
                *btmp, bufferManager->get_usingSize(*btmp) + sizeof(record));
            bufferManager->set_dirty(*btmp);
            return btmp->offsetNum;
        } else {
            btmp = bufferManager->getNextBlock(ftmp, btmp);
        }
    }
    return -1;
}

int RecordManager::deleteRecord(string table_name) {
    dropTable(table_name);
    createTable(table_name);
}

int RecordManager::deleteRecordconditional(string table_name,
                                           vector<Condition> conditions) {
    FileNode *ftmp =
        bufferManager->getFile(Gettablefilename(table_name).c_str());
    BlockNode *btmp = bufferManager->getBlockHead(ftmp);
    int count = 0;

    if (btmp == NULL) return -1;

    while (btmp != NULL) {
        int recordBlockNum = recordBlockDelete(table_name, conditions, btmp);
        count = count + recordBlockNum;
        if (btmp->isBottom)
            return count;
        else
            btmp = bufferManager->getNextBlock(ftmp, btmp);
    }

    return -1;
}

int RecordManager::selectRecord(string table_name,
                                vector<Condition> conditions) {
    FileNode *ftmp =
        bufferManager->getFile(tableFileNameGet(tableName).c_str());
    BlockNode *btmp = bufferManager->getBlockHead(ftmp);
    int count = 0;
    while (btmp != NULL) {
        int recordBlockNum = recordBlockFind(table_name, conditions, btmp);
        count = count + recordBlockNum;
        if (btmp->isBottom)
            return count;
        else
            btmp = bufferManager->getNextBlock(ftmp, btmp);
    }

    return -1;
}

int RecordManager::indexRecords(string tableName, string indexName) {
    fileNode *ftmp =
        bufferManager->getFile(tableFileNameGet(tableName).c_str());
    BlockNode *btmp = bufferManager->getBlockHead(ftmp);
    int count = 0;
    while (btmp != NULL) {
        int recordBlockNum =
            indexRecordBlockAlreadyInsert(tableName, indexName, btmp);
        count += recordBlockNum;
        if (btmp->isBottom)
            return count;
        else
            btmp = bufferManager->getNextBlock(ftmp, btmp);
    }

    return -1;
}
int RecordManager::indexRecordBlockAlreadyInsert(string table_name,
                                                 string index_name,
                                                 BlockNode *block) {
    if (block == NULL) {
        return -1;
    }
    int count = 0;

    char *recordBegin = bufferManager->get_content(*block);
    vector<Attribute> attribute;
    int recordSize = api->recordSizeGet(table_name);

    api->attributeGet(table_name, &attribute);

    int type;
    int typeSize;
    char *contentBegin;
    while (recordBegin < bufferManager->get_usingSize(*block) +
                             bufferManager->get_content(*block)) {
        contentBegin = recordBegin;
        for (int i = 0; i < attribute.size(); i++) {
            typeSize = api->typeSizeGet(attribute[i].type);

            if (attribute[i].index == index_name) {
                api->indexInsert(index_name, contentBegin, attribute[i].type,
                                 block->offsetNum);
                count++;
            }

            contentBegin += typeSize;
        }
        recordBegin += recordSize;
    }

    return count;
}

void RecordManager::init(API *a, BufferManager *b) {
    api = a;
    bufferManager = b;
}