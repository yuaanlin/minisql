#include <iostream>
#include "main.h"

using namespace std;

int main() {
    IndexManager indexManager;
    RecordManager recordManager;
    CatalogManager catalogManager;
    Interpreter interpreter;
    API api;
    BufferManager bufferManager;

    indexManager.init(&api, &bufferManager);
    recordManager.init(&api, &bufferManager);
    catalogManager.init(&api, &bufferManager);
    api.init(&interpreter, &catalogManager, &recordManager, &indexManager);
    bufferManager.init();
    interpreter.init(&api);
}