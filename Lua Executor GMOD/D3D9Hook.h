#pragma once
#include <Windows.h>
#include <iostream>
#include <filesystem>
#include <d3d9.h>
#include "../ImGui/imgui.h"
#include "../ImGui/imgui_impl_dx9.h"
#include "../ImGui/imgui_impl_win32.h"
#include <string>
#include <Psapi.h>
#include "detours.h"
#include "../ImGui/TextEditor.h"
#include "ImFileBrowser.h"
#include "LuaExecutor.h"
class D3D9Hook
{
private:
	bool menuOpen = false;

public:
	void KeyHandleThread();
	static DWORD WINAPI stKeyHandleThread();
	void InitializeHook();
	void ToggleMenuOpen();
	bool GetMenuOpen();
};

inline D3D9Hook* srcD3D9Hook = new D3D9Hook();