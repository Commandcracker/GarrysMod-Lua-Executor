#pragma once
#include <Windows.h>
#include <iostream>
class LuaExecutor
{
private:
	typedef void* (*CreateInterface)(const char *IName, int * IReturnCode);
	typedef int(__cdecl* _luaL_loadFile)(void* LState, char* LFilePath);
	typedef int(__cdecl* _luaL_loadString)(void* LState, char* LLuaCode);
	typedef int(__cdecl* _luaL_pCall)(void *LState, int nargs, int nresults, int errfunc);
	DWORD pGLuaState = NULL;
	DWORD CLuaInterface = NULL;
	bool LuaLoaded = false;
	_luaL_loadFile luaL_loadFile = NULL;
	_luaL_loadString luaL_loadString = NULL;
	_luaL_pCall luaL_pCall = NULL;

	enum LuaInterfaceType
	{
		LUAINTERFACE_CLIENT = 0,
		LUAINTERFACE_SERVER = 1,
		LUAINTERFACE_MENU = 2
	};

	class CLuaShared
	{
	public:
		virtual void            padding00() = 0;
		virtual void*			padding01() = 0;
		virtual void*			padding02() = 0;
		virtual void*			padding03() = 0;
		virtual void*			padding04() = 0;
		virtual void*			padding05() = 0;
		virtual DWORD			GetLuaInterface(LuaInterfaceType type) = 0;
	};

	CLuaShared* ILuaShared;

public:
	void InitLuaExecutor();
	void ExecuteFile(char* fileToExecute);
	void ExecuteString(char* stringToExecute);
};

inline LuaExecutor* GLuaExecutor = new LuaExecutor();