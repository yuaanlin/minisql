#ifndef __minisql_index_manager_h__
#define __minisql_index_manager_h__

class API;
class Interpreter;
class BufferManager;
class IndexManager {
   private:
    API *api;
    BufferManager *bufferManager;

   public:
    void init(API *a, BufferManager *b);
};

#endif