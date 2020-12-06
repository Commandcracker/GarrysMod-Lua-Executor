#include <Windows.h>
#include <iostream>
#include "LuaExecutor.h"
#include "D3D9Hook.h"

FILE* conFile; // Needed to allow prints to console

DWORD WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		HANDLE thread = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)D3D9Hook::stKeyHandleThread, NULL, NULL, NULL); // Create Exector Thread for the lua stuffs

		if (!thread)
			return FALSE; // Thread failed to create!

		CloseHandle(thread); // Prevent any memory leak
		AllocConsole(); // Allocates a console to game
		freopen_s(&conFile, "CONOUT$", "w", stdout); // Allow to print to console
		SetConsoleTitleA("Lua Executor [Debug]"); // Set a nice title instead of location path
		srcD3D9Hook->InitializeHook(); // Initialze DirectX9 Hook
		GLuaExecutor->InitLuaExecutor(); // Initialize all main modules
	}

	return TRUE; // Return success to injectors!
}
