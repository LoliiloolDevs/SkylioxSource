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

void LuaCExecution(std::string input) {
	try {
		std::vector<std::string> In = split(input);

		if (In.at(0) == "getfield") {
			r_lua_getfield(LuaState, stoi(In.at(1)), In.at(2).c_str());
		}

		else if (In.at(0) == "getglobal") {
			getglobal(LuaState, In.at(1).c_str());
		}

		else if (In.at(0) == "setfield") {
			r_lua_setfield(LuaState, stoi(In.at(1)), In.at(2).c_str());
		}

		else if (In.at(0) == "pushvalue") {
			r_lua_pushvalue(LuaState, stoi(In.at(1)));
		}

		else if (In.at(0) == "pushstring") {
			r_lua_pushstring(LuaState, In.at(1).c_str());
		}

		else if (In.at(0) == "pushnumber") {
			r_lua_pushnumber(LuaState, stoi(In.at(1)));
		}

		else if (In.at(0) == "pcall") {
			r_lua_pcall(LuaState, stoi(In.at(1)), stoi(In.at(2)), stoi(In.at(3)));

		}

		else if (In.at(0) == "emptystack") {
			r_lua_pushstring(LuaState, In.at(1).c_str());
		}

		else if (In.at(0) == "settop") {
			r_lua_settop(LuaState, stoi(In.at(1)));
		}
		else {
			Commands(input);
		}
	}
	catch (...) {

	}
}
