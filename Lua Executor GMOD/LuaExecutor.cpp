#include "LuaExecutor.h"
#define LUA_MULTRET -1

// Colour Stuff
HANDLE hConsole;

void error() {
	SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED);
	printf("ERROR\n");
	SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void success() {
	SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	printf("Success!\n");
	SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void LuaExecutor::InitLuaExecutor()
{
	// Colour Stuff
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	// Initializing Lua Functions
	printf("Initializing Lua Functions -> ");
	HMODULE luaShared = GetModuleHandleA("lua_shared.dll");
	if (!luaShared)
	{
		error();
		return;
	}
	success();

	// Loading Interface function
	printf("Loading Interface function -> ");
	CreateInterface CreateInterface_src = (CreateInterface)GetProcAddress(luaShared, "CreateInterface");
	ILuaShared = (CLuaShared*)CreateInterface_src("LUASHARED003", NULL);
	if (!ILuaShared)
	{
		error();
		return;
	}
	success();

	// Loading LuaL_LoadFile
	printf("Loading LuaL_LoadFile -> ");
	luaL_loadFile = (_luaL_loadFile)GetProcAddress(luaShared, "luaL_loadfile");
	if (!luaL_loadFile)
	{
		error();
		return;
	}
	success();

	// Loading LuaL_LoadString
	printf("Loading LuaL_LoadString -> ");
	luaL_loadString = (_luaL_loadString)GetProcAddress(luaShared, "luaL_loadstring");
	if (!luaL_loadString)
	{
		error();
		return;
	}
	success();

	// Loading Lua_pCall
	printf("Loading Lua_pCall -> ");
	luaL_pCall = (_luaL_pCall)GetProcAddress(luaShared, "lua_pcall");
	if (!luaL_pCall)
	{
		error();
		return;
	}
	success();

	LuaLoaded = true;
}

void LuaExecutor::ExecuteFile(char * fileToExecute)
{
	if (!LuaLoaded)
	{
		MessageBoxA(NULL, "Cant execute file when nothing is set!", "Error", 0);
		return;
	}

	// Loading CLuaInterface
	printf("Loading CLuaInterface -> ");
	CLuaInterface = ILuaShared->GetLuaInterface(LUAINTERFACE_CLIENT);
	if (!CLuaInterface)
	{
		error();
		return;
	}
	success();

	// Loading GLuaState
	printf("Loading GLuaState -> ");
	pGLuaState = *(DWORD*)(CLuaInterface + 0x4);
	if (!pGLuaState)
	{
		error();
		return;
	}
	success();

	luaL_loadFile((void*)pGLuaState, fileToExecute);
	luaL_pCall((void*)pGLuaState, 0, LUA_MULTRET, 0);
}

void LuaExecutor::ExecuteString(char * stringToExecute)
{
	if (!LuaLoaded)
	{
		MessageBoxA(NULL, "Cant execute string when nothing is set!", "Error", 0);
		return;
	}

	// Loading CLuaInterface
	printf("Loading CLuaInterface -> ");
	CLuaInterface = ILuaShared->GetLuaInterface(LUAINTERFACE_CLIENT);
	if (!CLuaInterface)
	{
		error();
		return;
	}
	success();

	// Loading GLuaState
	printf("Loading GLuaState -> ");
	pGLuaState = *(DWORD*)(CLuaInterface + 0x4);
	if (!pGLuaState)
	{
		error();
		return;
	}
	success();

	luaL_loadString((void*)pGLuaState, stringToExecute);
	luaL_pCall((void*)pGLuaState, 0, LUA_MULTRET, 0);
}
