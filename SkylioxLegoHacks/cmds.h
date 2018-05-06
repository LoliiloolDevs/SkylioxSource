#pragma once
#include <Windows.h>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <fstream>
#include <iterator>
#include <WinINet.h>
#include <algorithm>
#include <conio.h>
#include <Windows.h>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <fstream>
#include <iterator>
#include <WinINet.h>
#include <algorithm>
#include <random>
#include <typeinfo>
#include <random>
#include <typeinfo>
#include <fcntl.h>
#include <io.h>
#include <Windows.h>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <fstream>
#include <iterator>
#include <WinINet.h>
#include <algorithm>
#include <random>
#include <typeinfo>
#include "Scan.h"
#include "skylioxlua.h"
#include "rlua.h"
using namespace Rlua;
inline void Commands(std::string input) {
	std::vector<std::string> Input = split(input);

	if (to(Input.at(0)) == "ff") {
		if (to(Input.at(1)) == "me") {
			getglobal(LuaState, "game");
			r_lua_getfield(LuaState, -1, "Players");
			r_lua_getfield(LuaState, -1, "LocalPlayer");
			r_lua_getfield(LuaState, -1, "Character");
			getglobal(LuaState, "Instance");
			r_lua_getfield(LuaState, -1, "new");
			r_lua_pushstring(LuaState, "ForceField");
			r_lua_pushvalue(LuaState, -4);
			r_lua_pcall(LuaState, 2, 0, 0);
		}
		else {
			getglobal(LuaState, "game");
			r_lua_getfield(LuaState, -1, "Players");
			r_lua_getfield(LuaState, -1, Input.at(1).c_str());
			r_lua_getfield(LuaState, -1, "Character");
			getglobal(LuaState, "Instance");
			r_lua_getfield(LuaState, -1, "new");
			r_lua_pushstring(LuaState, "ForceField");
			r_lua_pushvalue(LuaState, -4);
			r_lua_pcall(LuaState, 2, 0, 0);
		}
	}
}