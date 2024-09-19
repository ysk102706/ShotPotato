#include "InputProcessor.h"

Keyboard InputProcessor::keyboard;
Mouse InputProcessor::mouse;

void InputProcessor::InitInput(HWND hwnd) {
	mouse.SetWindow(hwnd);

	// ���� ������ ��� ����� ��ġ
	mouse.SetMode(Mouse::MODE_RELATIVE);
}

bool InputProcessor::IsKeyDown(Keyboard::Keys key) {
	return keyboard.GetState().IsKeyDown(key);
}

bool InputProcessor::IsKeyUp(Keyboard::Keys key) {
	return keyboard.GetState().IsKeyUp(key);
}

Vector2 InputProcessor::MouseDragState() {
	Mouse::State state = mouse.GetState();
	return Vector2((float)state.x, (float)state.y);
}

Mouse::State InputProcessor::MouseState() {
	return mouse.GetState();
}