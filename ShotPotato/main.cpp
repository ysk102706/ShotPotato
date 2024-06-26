#include "Engine.h"

int WINAPI wWinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	PWSTR pCmdLine,
	int nCmdShow)
{
	Engine engine = Engine(hInstance, 1280, 8000, L"Show Potato");

	engine.Run();

	return 0;
}