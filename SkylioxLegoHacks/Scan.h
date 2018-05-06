#pragma once
#include <fcntl.h>
#include <tchar.h>
#include <windows.h>
#include "wtypes.h"
#include <istream>
#include <iostream>
#include <fstream>

inline long RoBlOxScAns(long RoBlOxScAn) {
	return (RoBlOxScAn - 0x400000 + (DWORD)GetModuleHandle(0));
}
namespace Module {
	bool Compare(const char* pScan, const char* bScan, const char* szScan)
	{
		while (*szScan) {
			if (*szScan != '?') {
				if (*pScan != *bScan) return 0;
			}
			++szScan, ++pScan, ++bScan;
		}
		return 1;
	}

	DWORD RbxKidScans(const char* RblxScan)
	{
		MEMORY_BASIC_INFORMATION RbxKidScan = { 0 };
		SYSTEM_INFO FEScan = { 0 };
		GetSystemInfo(&FEScan);
		DWORD StartFEScan = (DWORD)FEScan.lpMinimumApplicationAddress;
		DWORD EndFEScan = (DWORD)FEScan.lpMaximumApplicationAddress;
		do
		{
			while (VirtualQuery((void*)StartFEScan, &RbxKidScan, sizeof(RbxKidScan))) {
				if ((RbxKidScan.Protect & PAGE_READWRITE) && !(RbxKidScan.Protect & PAGE_GUARD))
				{
					for (DWORD i = (DWORD)(RbxKidScan.BaseAddress); i - (DWORD)(RbxKidScan.BaseAddress) < RbxKidScan.RegionSize; ++i)
					{
						if (Compare((const char*)i, RblxScan, "xxxx"))
							return i;
					}
				}
				StartFEScan += RbxKidScan.RegionSize;
			}
		} while (StartFEScan < EndFEScan);
		return 0;
	}
}