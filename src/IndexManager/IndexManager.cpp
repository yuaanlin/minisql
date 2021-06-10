#include "IndexManager.h"
#include "../BufferManager/BufferManager.h"

void IndexManager::init(API *a, BufferManager *b) {
    api = a;
    bufferManager = b;
}
