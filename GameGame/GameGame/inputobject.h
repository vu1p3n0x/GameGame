// FILE: inputobject.h
// DATE: 3/1/13
// DESC: declaraton of an object to manage external input

#ifndef INPUTOBJECT_H
#define INPUTOBJECT_H

#define DIRECTINPUT_VERSION 0x0800

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

#include <dinput.h>

class InputObject
{
private:
	HWND m_hwnd;

	IDirectInput8* m_directInput;
	IDirectInputDevice8* m_keyboard;
	IDirectInputDevice8* m_mouse;

	unsigned char m_keyboardState[256];
	unsigned char m_prevKeyboardState[256];
	DIMOUSESTATE m_mouseState;
	bool m_mouseLocked;
	
	int m_screenWidth, m_screenHeight;
	int m_mouseX, m_mouseY;

	bool IsPrevKeyPressed(unsigned long key);

public:
	InputObject();
	InputObject(const InputObject& inputobject);
	~InputObject();

	bool Initialize(HINSTANCE instance, HWND windowHandle, int screenWidth, int screenHeight);
	bool Update();
	void Shutdown();

	bool IsKeyTriggered(unsigned long key);
	bool IsKeyPressed(unsigned long key);
	bool IsKeyReleased(unsigned long key);

	void GetMouseLocation(int& positionX, int& positionY);

	void LockMouse();
	void ReleaseMouse();
};

#endif