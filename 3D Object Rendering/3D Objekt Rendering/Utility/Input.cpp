#include "Input.h"

Input::Input()
{
	HAxis = 0;
	VAxis = 0;
	QEAxis = 0;

	int cursorX = GetSystemMetrics(0) * 0.5f;
	int cursorY = GetSystemMetrics(1) * 0.5f;

	DeltaMouse = { 0.0f, 0.0f };
	SetCursorPos(cursorX, cursorY);

	ShowCursor(false);
}

void Input::Update(float deltaTime)
{
	int cursorX = GetSystemMetrics(0) * 0.5f;
	int cursorY = GetSystemMetrics(1) * 0.5f;
	
	POINT cursorPos;
	GetCursorPos(&cursorPos);
	
	DeltaMouse = { (float)cursorPos.x - cursorX, (float)cursorPos.y - cursorY };
	DeltaMouse.x *= 0.001f;
	DeltaMouse.y *= 0.001f;
	
	SetCursorPos(cursorX, cursorY);

	UpdateAxis(&VAxis, 'S', 'W', deltaTime);
	UpdateAxis(&HAxis, 'A', 'D', deltaTime);
	UpdateAxis(&QEAxis, 'Q', 'E', deltaTime);
}

void Input::UpdateAxis(float* axis, int nKey, int pKey, float deltaTime)
{
	float gravity = 8;
	float deadZone = 0.1f;

	if (GetAsyncKeyState(nKey) & 0x8000) *axis = *axis > -1.0f ? *axis - deltaTime * gravity : -1;
	else if (GetAsyncKeyState(pKey) & 0x8000) *axis = *axis <  1.0f ? *axis + deltaTime * gravity :  1;
	else 
	{
		if (*axis < 0)  *axis = *axis < -deadZone ? *axis + deltaTime * gravity : 0;
		else *axis = *axis > deadZone ? *axis - deltaTime * gravity : 0;
	}
}
