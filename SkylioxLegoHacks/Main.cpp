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
#include "cmds.h"
//////////////////////////////////////////////////////////////////////
using namespace std;

DWORD ScriptContext = RoBlOxScAns(0x6B6EC6);

void Console(char* title) {
	AllocConsole();
	SetConsoleTitleA(title);
	freopen("CONOUT$", "w", stdout);
	freopen("CONIN$", "r", stdin);
	HWND ConsoleHandle = GetConsoleWindow();
	::SetWindowPos(ConsoleHandle, NULL, 0, 0, 0, 0, SWP_DRAWFRAME | SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
	::ShowWindow(ConsoleHandle, SW_NORMAL);
}

void ConsoleHacks()
{
	DWORD nothing;
	VirtualProtect((PVOID)&FreeConsole, 1, PAGE_EXECUTE_READWRITE, &nothing);
	*(BYTE*)(&FreeConsole) = 0xC3;
}
inline void Commands(std::string input);
DWORD WINAPI CmdPipe(PVOID lvpParameter)
{
	char shitty[1024];
	HANDLE ok;
	DWORD oklol;
	ok = CreateNamedPipe(TEXT("\\\\.\\pipe\\NoobPipe"),
		PIPE_ACCESS_DUPLEX | PIPE_TYPE_BYTE | PIPE_READMODE_BYTE,
		PIPE_WAIT,
		1,
		1024 * 16,
		1024 * 16,
		NMPWAIT_USE_DEFAULT_WAIT,
		NULL);
	while (ok != INVALID_HANDLE_VALUE)
	{
		if (ConnectNamedPipe(shitty, NULL) != FALSE)
		{
			while (ReadFile(ok, shitty, sizeof(shitty) - 1, &oklol, NULL) != FALSE)
			{
				shitty[oklol] = '\0';
				try {
					Commands(shitty);
				}
				catch (std::exception e) {
					MessageBox(NULL, e.what(), "Error", MB_OK);
				}
				catch (...) {
					MessageBox(NULL, "Error", "Error", MB_OK);
					cout << "Error" << endl;
				}
			}
		}
		DisconnectNamedPipe(ok);
	}
}

std::string Input() {
	std::string Lithium;
	getline(std::cin, Lithium);
	return Lithium;
}
void Main() {
	//LuaSatetScan
	DWORD Scc = *(DWORD*)(ScriptContext + 0x2);
	DontUpdateMe = Module::RbxKidScans((char*)&Scc);
	dmodel = GetGey(DontUpdateMe);
	wspace = FindFirstGey(dmodel, "Workspace");
	light = FindFirstGey(dmodel, "Lighting");
	plrs = FindFirstGey(dmodel, "Players");
	LuaState = (DontUpdateMe + 56 * DontUpdateMePl0x + 164) ^ *(DWORD *)(DontUpdateMe + 56 * DontUpdateMePl0x + 164);
	/////////////////////////////////////////////////////////////////////////////////////
	MessageBoxA(NULL, "Loaded Baby [:", "Skyliox", NULL);
	ConsoleHacks();
	Console("Skyliox | Open Source Exploits");

	while (true) {
			std::cout  << "> " ;
			std::string Z = Input();
			Commands(Z);
	}

}
BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved

)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hModule);
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)&Main, NULL, NULL, NULL);

	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}
