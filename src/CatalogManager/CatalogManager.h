#ifndef __catalog_manager_h__
#define __catalog_manager_h__

#include "API.h"
#include "BufferManager.h"

class CatalogManager {
   private:
    API *api;
    BufferManager *bufferManager;

   public:
    void init(API *a, BufferManager *b);
};

#endif