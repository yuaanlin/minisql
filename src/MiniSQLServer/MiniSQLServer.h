#ifndef __minisql_server_h__
#define __minisql_server_h__

#include "../CatalogManager/CatalogManager.h"
#include "../FakeRecordManager/FakeRecordManager.h"
#include "../IndexManager/IndexManager.h"
#include "../Interpreter/Interpreter.h"
#include "../BufferManager/BufferManager.h"
#include "../API/API.h"

class MiniSQLServer {
   private:
    IndexManager *indexManager;
    FakeRecordManager *recordManager;
    CatalogManager *catalogManager;
    Interpreter *interpreter;
    API *api;
    BufferManager *bufferManager;

   public:
    MiniSQLServer();
    void run();
};

#endif