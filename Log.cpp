#include "Log.h"
#include <iostream>

std::vector<LogEntry> Log::logEntries;

void Log::INFO(const std::string& msg, bool preSpaced, bool postSpaced)
{
    LogEntry entry;

    entry.type = LogType::INFO;
    entry.message = "\x1B[32m[INFO]\t" + msg;
    entry.preSpaced = preSpaced;
    entry.postSpaced = postSpaced;

    logEntries.push_back(entry);
    PrintLog(entry);
}

void Log::WARNING(const std::string& msg, bool preSpaced, bool postSpaced)
{
    LogEntry entry;

    entry.type = LogType::WARNING;
    entry.message = "\x1B[33m[WARNING]\t" + msg;
    entry.preSpaced = preSpaced;
    entry.postSpaced = postSpaced;

    logEntries.push_back(entry);
    PrintLog(entry);
}

void Log::ERROR(const std::string& msg, bool preSpaced, bool postSpaced)
{
    LogEntry entry;

    entry.type = LogType::ERROR;
    entry.message = "\x1B[91m[ERROR]\t" + msg;
    entry.preSpaced = preSpaced;
    entry.postSpaced = postSpaced;

    logEntries.push_back(entry);
    PrintLog(entry);
}

void Log::SEPARATOR()
{
    std::cout << "----------------------------------------" << std::endl;
}

void Log::PrintLog(LogEntry entry)
{
    if (entry.preSpaced)
    {
        std::cout << std::endl;
    }

    std::cout << entry.message << +"\x1B[0m" << std::endl;

    if (entry.postSpaced)
    {
        std::cout << std::endl;
    }
}
