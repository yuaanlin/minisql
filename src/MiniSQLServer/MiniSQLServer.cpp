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
    this->recordManager = new FakeRecordManager();

    FileLogger *logger = new FileLogger();

    logger->log("Starting MiniSQL Server ...");
    cout << "MiniSQL starting initialize and load data ..." << endl;

    this->catalogManager->init(logger);
    this->recordManager->init(logger, this->catalogManager);
    this->indexManager->init(this->recordManager);
    this->api->init(this->catalogManager, this->recordManager,
                    this->indexManager, logger);
    this->bufferManager->init();
    this->interpreter->init(this->api, logger, this->catalogManager);

    logger->log("MiniSQL Server initialized complete!");
    cout << "MiniSQL Server initialized complete!" << endl;
}

void MiniSQLServer::run() {
    Server httpServer;

    httpServer.Post("/minisql", [&](const Request &req, Response &res,
                                    const ContentReader &content_reader) {
        std::string requestBody;
        content_reader([&](const char *data, size_t data_length) {
            requestBody.append(data, data_length);
            return true;
        });

        vector<string> cmds;
        string temp = "";
        for (auto c : requestBody) {
            if (c == '\n') continue;
            if (c == '\0') continue;
            if (c == ';') {
                cmds.push_back(temp);
                temp = "";
                continue;
            }
            temp.push_back(c);
        }

        ExecutionResponse allCommandResponse;
        /* Send sql_command to interpreter and get response */
        for (auto cmd : cmds) {
            OneCommandExecutionResponse oneCommandResponse =
                this->interpreter->execute(cmd);
            ExecutionMessage *msg = new ExecutionMessage();
            allCommandResponse.fields = oneCommandResponse.fields;
            allCommandResponse.results = oneCommandResponse.results;
            msg->command = oneCommandResponse.cmd;
            msg->message = oneCommandResponse.msg;
            allCommandResponse.messages.push_back(*msg);
        }

        res.set_content(allCommandResponse.getJson(), "application/json");
        this->recordManager->saveTablesToFiles();
    });

    cout << "Starting server..." << endl;
    cout << "Send POST request to port 3306 to execute SQL command." << endl;

    httpServer.listen("localhost", 3306);

    cout << "Closing server ..." << endl;
}