#ifndef __minisql_api_h__
#define __minisql_api_h__

#include "CatalogManager.h"
#include "RecordManager.h"
#include "IndexManager.h"
#include "Interpreter.h"

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