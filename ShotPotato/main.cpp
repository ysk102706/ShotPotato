#include "Window.h"

int WINAPI wWinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	PWSTR pCmdLine,
	int nCmdShow)
{
	Window::InitWindow(hInstance, 1280, 800, L"Shot Potato");

	while (1) {}

	return 0;
}