#ifndef __minisql_index_manager_h__
#define __minisql_index_manager_h__

#include "API.h"
#include "BufferManager.h"

class IndexManager {
   private:
    API *api;
    BufferManager *bufferManager;

   public:
    IndexManager(API *a, BufferManager *b);
};

#endif