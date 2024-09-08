#include "Window.h"

int Window::width;
int Window::height;
HWND Window::hwnd;
HINSTANCE Window::hInstance;
std::wstring Window::title;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

bool Window::InitWindow(HINSTANCE hInstance, int width, int height, std::wstring title) {
	Window::hInstance = hInstance;
	Window::width = width;
	Window::height = height;
	Window::title = title;

	WNDCLASS wc;
	ZeroMemory(&wc, sizeof(wc));

	wc.hInstance = hInstance; 
	wc.lpszClassName = TEXT("Shot Potato"); 
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION); 
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW); 
	wc.lpfnWndProc = WndProc; 

	if (RegisterClass(&wc) == false) exit(-1);

	RECT rect = { 0, 0, width, height };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false); 
	width = rect.right - rect.left;
	height = rect.bottom, rect.top;

	hwnd = CreateWindow(
		wc.lpszClassName, 
		title.c_str(),
		WS_OVERLAPPEDWINDOW, 
		0, 0, 
		width, height, 
		NULL, NULL, 
		hInstance, 
		NULL
	);

	if (hwnd == nullptr) return false;

	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);

	return true;
}

HWND Window::GetHWND() {
	return hwnd;
}

int Window::Width() {
	return width;
}

int Window::Height() {
	return height;
}