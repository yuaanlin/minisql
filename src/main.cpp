#include "MiniSQLServer/MiniSQLServer.h"
#include <iostream>

using namespace std;

int main(void) {
    MiniSQLServer server;
    cout << "Starting server..." << endl;
    cout << "Send POST request to port 3306 to execute SQL command." << endl;
    server.run();
    cout << "Closing server ..." << endl;
}
