#pragma once
#include <Windows.h>
#include <string>

class Window {
public:
	static bool InitWindow(HINSTANCE hInstance, int width, int height, std::wstring title);
	static HWND GetHWND();
	static int Width();
	static int Height();

private:
	static int width;
	static int height;
	static std::wstring title;
	static HWND hwnd;
	static HINSTANCE hInstance;
};