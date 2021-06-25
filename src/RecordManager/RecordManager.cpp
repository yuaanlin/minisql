#include "../RecordManager/RecordManager.h"
#include "../API/API.h"

void RecordManager::init(API *a, BufferManager *b) {
    api = a;
    bufferManager = b;
}

void RecordManager::createTable(string table_name) {}

void RecordManager::dropTable(string table_name) {}

void RecordManager::updateRecord(string tableName, vector<string> fields,
                                 vector<string> values,
                                 vector<Condition> conditions) {}

void RecordManager::insertRecord(string table_name, vector<string> record) {}

int RecordManager::deleteRecord(string table_name) { return 0; }

int RecordManager::deleteRecord(string table_name,
                                vector<Condition> conditions) {
    return 0;
}

Records RecordManager::selectRecord(string tableName,
                                    vector<Condition> conditions) {
    Records r;
    return r;
}

Records RecordManager::selectRecordByOffset(string tableName,
                                            vector<Condition> conditions,
                                            int offset) {
    Records r;
    return r;
}

void RecordManager::indexRecords(string tableName, string attrName) {}