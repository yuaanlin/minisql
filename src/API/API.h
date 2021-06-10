#ifndef __minisql_api_h__
#define __minisql_api_h__

#include "../CatalogManager/CatalogManager.h"
#include "../RecordManager/RecordManager.h"
#include "../IndexManager/IndexManager.h"
#include "../Interpreter/Interpreter.h"

class API {
   private:
    Interpreter *interpreter;
    CatalogManager *catalogManager;
    RecordManager *recordManager;
    IndexManager *indexManager;

   public:
    void init(Interpreter *it, CatalogManager *c, RecordManager *r,
              IndexManager *ind);
};

#endif