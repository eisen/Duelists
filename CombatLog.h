#pragma once
#include <string>
#include <vector>
#include <raylib.h>

#define ENTRY_SHORT_DURATION 3.0f

struct CombatEntry
{
    std::string message;
    Color color;
    float duration;
    bool preSpaced = false;
    bool postSpaced = false;
    float timer = 0;
};

class CombatLog
{
    static std::vector<CombatEntry> logEntries;
    static int posY;

public:
    static void Init();
    static void AddEntry(const CombatEntry& msg);
    static void SEPARATOR();
    static void DrawEntry(const CombatEntry& entry);
    static void ProcessLog();
    static void DrawEntryAt(const std::string& msg, int xPos, int yPos, Color color);
};