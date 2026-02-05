#include <iostream>
#include <raylib.h>
#include <map>

#include "Log.h"

std::vector<LogEntry> Log::logEntries;
int Log::posY;

#define LINE_HEIGHT 15
#define LINE_HEIGHT 14

std::map<LogType, Color> levelToColor {
    {Default, WHITE},
    {INFO, GREEN},
    {WARNING, ORANGE},
    {ERROR, RED}
};

void Log::INFO(const std::string& msg, bool preSpaced, bool postSpaced)
{
    LogEntry entry;

    entry.type = LogType::INFO;
    entry.message = msg;
    entry.preSpaced = preSpaced;
    entry.postSpaced = postSpaced;

    logEntries.push_back(entry);
    PrintLog(entry);
}

void Log::WARNING(const std::string& msg, bool preSpaced, bool postSpaced)
{
    LogEntry entry;

    entry.type = LogType::WARNING;
    entry.message = msg;
    entry.preSpaced = preSpaced;
    entry.postSpaced = postSpaced;

    logEntries.push_back(entry);
    PrintLog(entry);
}

void Log::ERROR(const std::string& msg, bool preSpaced, bool postSpaced)
{
    LogEntry entry;

    entry.type = LogType::ERROR;
    entry.message = msg;
    entry.preSpaced = preSpaced;
    entry.postSpaced = postSpaced;

    logEntries.push_back(entry);
    PrintLog(entry);
}

void Log::SEPARATOR()
{
    PrintLog({ LogType::Default, "----------------------------------------", false, false });
}

void Log::Init()
{
    logEntries.clear();
    posY = 400;
}

void Log::PrintLog(LogEntry entry)
{
    if (entry.preSpaced)
    {
        posY += LINE_HEIGHT;
    }

    DrawText(entry.message.c_str(), 20, posY, LINE_HEIGHT, levelToColor[entry.type]);
    posY += LINE_HEIGHT;

    if (entry.postSpaced)
    {
        posY += LINE_HEIGHT;
    }

    if (posY > 600)
    {
        posY = 10;
    }
}
