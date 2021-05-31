#ifndef __minisql_record_manager__
#define __minisql_record_manager__

#include "API.h"
#include "BufferManager.h"

class RecordManager {
   private:
    API *api;
    BufferManager *bufferManager;

   public:
    RecordManager(API *a, BufferManager *b);
};

#endif