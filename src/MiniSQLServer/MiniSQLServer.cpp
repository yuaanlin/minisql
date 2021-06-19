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
    api.init(&catalogManager, &recordManager, &indexManager);
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
        ExecutionResponse exeRes = this->interpreter.execute(sqlCommand);

        res.set_content(exeRes.getJson(), "application/json");
    });

    cout << "Starting server..." << endl;
    cout << "Send POST request to port 3306 to execute SQL command." << endl;

    httpServer.listen("localhost", 3306);

    cout << "Closing server ..." << endl;
}