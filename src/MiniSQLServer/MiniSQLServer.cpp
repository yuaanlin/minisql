#include "MiniSQLServer.h"
#include "../../include/httplib.h"
#include <iostream>

using namespace httplib;

MiniSQLServer::MiniSQLServer() {
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

    this->api = api;
    this->bufferManager = bufferManager;
    this->catalogManager = catalogManager;
    this->indexManager = indexManager;
    this->interpreter = interpreter;
    this->recordManager = recordManager;
}

void MiniSQLServer::run() {
    Server httpServer;

    httpServer.Post("/minisql", [&](const Request &req, Response &res,
                                    const ContentReader &content_reader) {
        std::string sqlCommand;
        content_reader([&](const char *data, size_t data_length) {
            sqlCommand.append(data, data_length);
            return true;
        });

        /* Send sql_command to interpreter and get response */

        res.set_content("MiniSQL not implemented yet.", "application/json");
    });

    httpServer.listen("localhost", 3306);
}