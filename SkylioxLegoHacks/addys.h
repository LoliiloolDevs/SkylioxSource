#pragma once
#include <tchar.h>
#include <windows.h>
#include "wtypes.h"
#include <istream>
#include <iostream>
#include <fstream>
#include <string>
#include "Scan.h"
#include "skylioxlua.h"
#include "rlua.h"

// Roblox Lua Addresses
unsigned long lua_GetField = RoBlOxScAns(0x0000000);
unsigned long lua_PushString = RoBlOxScAns(0x0000000);
unsigned long lua_PushValue = RoBlOxScAns(0x0000000);
unsigned long lua_PushNumber = RoBlOxScAns(0x0000000);
unsigned long lua_Pcall = RoBlOxScAns(0x0000000);
unsigned long lua_Call = RoBlOxScAns(0x0000000);
unsigned long lua_SetField = RoBlOxScAns(0x0000000);
unsigned long lua_PushNil = RoBlOxScAns(0x0000000);
unsigned long ScriptContext = RoBlOxScAns(0x6B6EC6);
////////////////////////////////////////