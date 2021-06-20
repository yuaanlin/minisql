#include "MiniSQLServer.h"
#include "../../include/httplib.h"
#include "../FileLogger/FileLogger.h"
#include <iostream>

using namespace httplib;

MiniSQLServer::MiniSQLServer() {
    this->api = new API();
    this->bufferManager = new BufferManager();
    this->catalogManager = new CatalogManager();
    this->indexManager = new IndexManager();
    this->interpreter = new Interpreter();
    this->recordManager = new RecordManager();

    FileLogger *logger = new FileLogger();

    logger->log("Starting MiniSQL Server ...");

    this->indexManager->init(this->api, this->bufferManager);
    this->recordManager->init(this->api, this->bufferManager);
    this->catalogManager->init(this->api, logger);
    this->api->init(this->catalogManager, this->recordManager,
                    this->indexManager, logger);
    this->bufferManager->init();
    this->interpreter->init(this->api, logger);
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
        ExecutionResponse exeRes = this->interpreter->execute(sqlCommand);

        res.set_content(exeRes.getJson(), "application/json");
    });

    cout << "Starting server..." << endl;
    cout << "Send POST request to port 3306 to execute SQL command." << endl;

    httpServer.listen("localhost", 3306);

    cout << "Closing server ..." << endl;
}