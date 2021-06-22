#include "FileLogger.h"
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

string getTodayDate() {
    time_t rawtime;
    struct tm *timeinfo;
    char buffer[80];
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", timeinfo);
    string todayDate(buffer);
    return todayDate;
}

string getCurrentTime() {
    time_t rawtime;
    struct tm *timeinfo;
    char buffer[80];
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
    std::string currentTime(buffer);
    return currentTime;
}

void FileLogger::log(string s) {
    ofstream log;

    if (!fs::is_directory("logs")) {
        fs::create_directory("logs");
    }

    log.open("logs/" + getTodayDate() + ".log",
             fstream::in | fstream::out | fstream::app);

    log << '[' << getCurrentTime() << "] " << s << endl;

    log.close();
}