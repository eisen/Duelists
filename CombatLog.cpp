#include <iostream>
#include <raylib.h>
#include <map>

#include "CombatLog.h"

std::vector<CombatEntry> CombatLog::logEntries;
int CombatLog::posY;

#define LINE_HEIGHT 15
#define START_Y_POS 400
#define MAX_ENTRIES 6

void CombatLog::AddEntry(const CombatEntry& entry)
{
    logEntries.push_back(entry);

    if (logEntries.size() > MAX_ENTRIES)
    {
        logEntries.erase(logEntries.begin());
    }
}

void CombatLog::SEPARATOR()
{
    CombatEntry separator = {"----------------------------------------", WHITE, 3.0f, 0,false, false };
    AddEntry(separator);
}

void CombatLog::Init()
{
    logEntries.clear();
}

void CombatLog::DrawEntry(const CombatEntry& entry)
{
    if (entry.preSpaced)
    {
        posY += LINE_HEIGHT;
    }

    DrawText(entry.message.c_str(), 20, posY, LINE_HEIGHT, entry.color);
    posY += LINE_HEIGHT;

    if (entry.postSpaced)
    {
        posY += LINE_HEIGHT;
    }

    if (posY > 600)
    {
        posY = START_Y_POS;
    }
}

void CombatLog::ProcessLog()
{
    posY = START_Y_POS;
    for (size_t idx = 0; idx < logEntries.size();)
    {
        auto entry = logEntries[idx];
        DrawEntry(entry);
        entry.timer += GetFrameTime();

        if (entry.timer > entry.duration)
        {
            logEntries.erase(logEntries.begin() + idx);
        }
        else
        {
            ++idx;
        }
    }
}

void CombatLog::DrawEntryAt(const std::string& msg, int xPos, int yPos, Color color)
{
    DrawText(msg.c_str(), xPos + 2, yPos + 2, 20, BLACK);
    DrawText(msg.c_str(), xPos, yPos, 20, color);
}
