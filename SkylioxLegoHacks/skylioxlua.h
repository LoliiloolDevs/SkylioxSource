#pragma once
#include <tchar.h>
#include <windows.h>
#include "wtypes.h"
#include <istream>
#include <iostream>
#include <fstream>
#include <string>
#include "Scan.h"
#include "rlua.h"
int dmodel = 0;
int wspace = 0;
int light = 0;
int plrs = 0;
int DontUpdateMe;
int LuaState;
int DontUpdateMePl0x = 1;

std::vector<std::string> split(std::string s) {

	std::vector<std::string> elems;
	std::stringstream ss(s);
	std::istream_iterator<std::string> begin(ss);
	std::istream_iterator<std::string> end;
	std::vector<std::string> vstrings(begin, end);
	return vstrings;
}
std::string to(std::string str)
{
	std::string enter("");
	for (size_t i = 0; i < str.length(); i++)
	{
		int aenter = (int)str.at(i);
		if (aenter >= (int)'a' && aenter <= (int)'z')
			enter += (char)aenter;
		else
			enter += (char)(aenter + ((int)'a' - (int)'A'));
	}
	return enter;
}
const char* GeyClass(int self)
{
	try {
		return (const char*)(*(int(**)(void))(*(int*)self + 16))();
	}
	catch (...) {
		printf("gey");
	}
}
int FindFirstGey(int Instance, const char* Name)
{
	try {
		DWORD StartOfChildren = *(DWORD*)(Instance + 0x2C);
		DWORD EndOfChildren = *(DWORD*)(StartOfChildren + 4);

		for (int i = *(int*)StartOfChildren; i != EndOfChildren; i += 8)
		{
			if (memcmp(GeyClass(*(int*)i), Name, strlen(Name)) == 0)
			{
				return *(int*)i;
			}
		}
	}
	catch (...) {
		printf("gey");
	}
}
int GetGey(int Instance) {
	try {
		return *(int*)(Instance + 0x34);
	}
	catch (...) {
		printf("gey");
	}
}
int GetFilteringEnabled(int Workspace) {
	return *(BYTE*)(Workspace + 0x25B);
}

// Take From Zero So Credits To Zero Owner & Rakion99 because he update Zer0 <3