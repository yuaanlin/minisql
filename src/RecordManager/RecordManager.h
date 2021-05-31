#ifndef __minisql_record_manager__
#define __minisql_record_manager__

#include "API.h"
#include "BufferManager.h"

class RecordManager {
   private:
    API *api;
    BufferManager *bufferManager;

   public:
    void init(API *a, BufferManager *b);
};

#endif