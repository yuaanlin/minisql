#include "MiniSQLServer/MiniSQLServer.h"
#include <iostream>
#include <fstream>
#include "FakeRecordManager/FakeRecordManager.h"

using namespace std;

int main(void) {
    MiniSQLServer server;
    server.run();
}
