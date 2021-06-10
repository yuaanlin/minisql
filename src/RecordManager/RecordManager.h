#ifndef __minisql_record_manager__
#define __minisql_record_manager__

class API;
class BufferManager;
class RecordManager {
   private:
    API *api;
    BufferManager *bufferManager;

   public:
    void init(API *a, BufferManager *b);
};

#endif