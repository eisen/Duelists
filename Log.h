#pragma once
#include <string>
#include <vector>

enum LogType
{
    INFO = 0,
    WARNING,
    ERROR
};

struct LogEntry
{
    LogType type;
    std::string message;
    bool preSpaced;
    bool postSpaced;
};

class Log
{
public:
    static std::vector<LogEntry> logEntries;
    static void INFO(const std::string& msg, bool preSpaced = false, bool postSpaced = false);
    static void WARNING(const std::string& msg, bool preSpaced = false, bool postSpaced = false);
    static void ERROR(const std::string& msg, bool preSpaced = false, bool postSpaced = false);
    static void SEPARATOR();
    static void PrintLog(LogEntry entry);
};