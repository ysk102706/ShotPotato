#pragma once
#include <Windows.h>
#include <DirectXTK/Keyboard.h>
#include <DirectXTK/Mouse.h>
#include "Vector2.h"

using DirectX::Keyboard;
using DirectX::Mouse;

class InputProcessor {
public:
	static void InitInput(HWND hwnd);
	static bool IsKeyDown(Keyboard::Keys key);
	static bool IsKeyUp(Keyboard::Keys key);

	static void ResetKeyboardState() { keyboard.Reset(); }

	static Vector2 MouseDragState();
	static Mouse::State MouseState();

private:
	static Keyboard keyboard;
	static Mouse mouse;
};