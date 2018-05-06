#pragma once

typedef int(SkylioxState);

#define r_lua_getglobal -10002
#define getglobal(l,g)			 Rlua::r_lua_getfield(l, r_lua_getglobal, g)



DWORD retc(DWORD addr)
{
	BYTE* tAddr = (BYTE*)addr;

	/*  Calcualte the size of the function.

	In theory this will run until it hits the next
	functions prolog. It assumes all calls are aligned to
	16 bytes. (grazie katie)
	*/
	do
	{
		tAddr += 16;
	} while (!(tAddr[0] == 0x55 && tAddr[1] == 0x8B && tAddr[2] == 0xEC));

	DWORD funcSz = tAddr - (BYTE*)addr;

	/* Allocate memory for the new function */
	PVOID nFunc = VirtualAlloc(NULL, funcSz, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	if (nFunc == NULL)
		return addr;

	/* Copy the function to the newly allocated memory */
	memcpy(nFunc, (void*)addr, funcSz);

	BYTE* pos = (BYTE*)nFunc;
	BOOL valid = false;
	do
	{
		/*  Check for the return check with the sig:
		72 ?? A1 ?? ?? ?? ?? 8B

		If the sig matches replace the the jb with a jmp.
		*/
		if (pos[0] == 0x72 && pos[2] == 0xA1 && pos[7] == 0x8B) {
			*(BYTE*)pos = 0xEB;

			DWORD cByte = (DWORD)nFunc;
			do
			{
				/*  Check if the current byte is a call, if it is,
				calculate the new relative call(s).

				*(->E8 + 1) = originalFunction - nextInstruction

				oFuncPos - Position of call in original function
				= originalFunction + (->E8 - newFunction)

				oFuncAddr - Original call location
				= oFuncPos + rel32Offset + sizeof(call)

				relativeAddr - New relative address
				= oFuncAddr - ->E8 - sizeof(call)

				Since we are not using a disassembler we assume
				that if we hit a E8 byte which is properly aligned
				it is a relative call.
				For a small amount of compensation I skip the location
				of the call, since it is possible to have the byte
				E8 inside of it.
				*/
				if (*(BYTE*)cByte == 0xE8)
				{
					DWORD oFuncPos = addr + (cByte - (DWORD)nFunc);
					DWORD oFuncAddr = (oFuncPos + *(DWORD*)(oFuncPos + 1)) + 5;

					if (oFuncAddr % 16 == 0)
					{
						DWORD relativeAddr = oFuncAddr - cByte - 5;
						*(DWORD*)(cByte + 1) = relativeAddr;

						/* Don't check rel32 */
						cByte += 4;
					}
				}

				cByte += 1;
			} while (cByte - (DWORD)nFunc < funcSz);

			valid = true;
		}
		pos += 1;
	} while ((DWORD)pos < (DWORD)nFunc + funcSz);

	/* This function has no return check, let's not waste memory */
	if (!valid)
	{
		VirtualFree(nFunc, funcSz, MEM_RELEASE);
		return addr;
	}

	return (DWORD)nFunc;
}
DWORD getfielld = RoBlOxScAns(0x73E630);
DWORD pushstringg = RoBlOxScAns(0x73F990);
DWORD pcallll = RoBlOxScAns(0x73F3E0);
namespace Rlua {

	typedef int(__cdecl*Lua_getf)(SkylioxState lst, int index, const char *k);
	Lua_getf r_lua_getfield = (Lua_getf)retc(getfielld);

	typedef int(__fastcall*lua_pushstring)(SkylioxState lst, const char *s);
	lua_pushstring r_lua_pushstring = (lua_pushstring)pushstringg;

	typedef int(__cdecl *lua_pushvalue)(SkylioxState lst, int index);
	lua_pushvalue r_lua_pushvalue = (lua_pushvalue)retc(RoBlOxScAns(0x73FA40));

	//typedef int(__cdecl*lua_call)(SkylioxState lst, int nargs, int nresults);
	//lua_call r_lua_call = (lua_call)retc(RoBlOxScAns(0x73E030));

	//typedef int(__stdcall*lua_setfields)(SkylioxState lst, int index, const char *k);
	//lua_setfields r_lua_setfield2 = (lua_setfields)retc(RoBlOxScAns(0x740350));

	//typedef int(__thiscall*lua_pushnumber)(SkylioxState lst, double n);
	//lua_pushnumber r_lua_pushnumber = (lua_pushnumber)retc(RoBlOxScAns(0x73F900));

	//typedef void*(__cdecl *contextlvl)();
	//contextlvl r_lua_level = (contextlvl)RoBlOxScAns(0x597DA0);

	typedef int(__cdecl*Lua_pcallss)(SkylioxState lst, int nargs, int nresults, int errfunc);
	Lua_pcallss r_lua_pcall1 = (Lua_pcallss)retc(pcallll);

	//typedef int(__cdecl*Lua_pushnil)(SkylioxState lst);
	//Lua_pushnil r_lua_pushnil = (Lua_pushnil)retc(RoBlOxScAns(0x73F890));

	//typedef int(__cdecl*Lua_settop)(SkylioxState lst, int index);
	//Lua_settop r_lua_settop = (Lua_settop)retc(RoBlOxScAns(0x740720));

	//typedef signed int(__fastcall*lua_getmetatable)(SkylioxState lst, int idx);
	//lua_getmetatable r_lua_getmetatable = (lua_getmetatable)retc(RoBlOxScAns(0x73E8F0));

}
using namespace Rlua;


void r_lua_pcall(SkylioxState lst, int nargs, int nresults, int errfunc) {
	WriteProcessMemory(GetCurrentProcess(), reinterpret_cast<void*>(RoBlOxScAns(0x737797)), "\xEB", 1, 0);
	Rlua::r_lua_pcall1(lst, nargs, nresults, errfunc);
	WriteProcessMemory(GetCurrentProcess(), reinterpret_cast<void*>(RoBlOxScAns(0x737797)), "\x74", 1, 0);
}


/*#define pop(L,n)            Rlua::r_lua_settop(L, -(n)-1)
void r_lua_setfield(int L, int idx, const char *k) {

	using namespace Rlua;
	r_lua_pushvalue(L, idx);
	if (r_lua_getmetatable(L, -1)) {
		r_lua_getfield(L, -1, "__newindex");
		r_lua_pushvalue(L, -3);
		r_lua_pushstring(L, k);
		r_lua_pushvalue(L, -6);
		r_lua_pcall(L, 3, 0, 0);
		pop(L, 3);
	}
	else {
		pop(L, 1);
		r_lua_setfield2(L, idx, k);
	}
}*/