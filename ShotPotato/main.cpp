#include "Engine.h"

int WINAPI wWinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	PWSTR pCmdLine,
	int nCmdShow)
{
	Engine engine(hInstance, 1280, 800, L"Show Potato");

	engine.Run();

	return 0;
}