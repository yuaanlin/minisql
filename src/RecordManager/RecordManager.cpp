#include "../RecordManager/RecordManager.h"
#include "../API/API.h"

void RecordManager::init(API *a, BufferManager *b) {
    api = a;
    bufferManager = b;
}