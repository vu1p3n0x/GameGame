// FILE: inputobject.h
// DATE: 3/1/13
// DESC: declaraton of an object to manage external input

#ifndef INPUTOBJECT_H
#define INPUTOBJECT_H

#define DIRECTINPUT_VERSION 0x0800

#define INPUTOBJECT_KEYBOARD_MAX 256
#define INPUTOBJECT_MOUSE_MAX 4

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

#include <dinput.h>

class InputObject
{
private:
	HWND m_hwnd;
	int m_screenWidth;
	int m_screenHeight;

	IDirectInput8* m_directInput;

	IDirectInputDevice8* m_keyboard;
	unsigned char m_keyboardState[256];
	unsigned char m_prevKeyboardState[256];

	IDirectInputDevice8* m_mouse;
	DIMOUSESTATE m_mouseState;
	DIMOUSESTATE m_prevMouseState;
	bool m_mouseLocked;
	int m_mouseX;
	int m_mouseY;

	bool IsPrevKeyPressed(unsigned int key);
	bool IsPrevButtonPressed(unsigned int button);

public:
	InputObject();
	InputObject(const InputObject& inputobject);
	~InputObject();

	bool Initialize(HINSTANCE instance, HWND windowHandle, int screenWidth, int screenHeight);
	bool Update();
	void Shutdown();

	bool IsKeyTriggered(unsigned int key);
	bool IsKeyPressed(unsigned int key);
	bool IsKeyReleased(unsigned int key);

	void GetMouseLocation(int& positionX, int& positionY);
	
	bool IsButtonTriggered(unsigned int button);
	bool IsButtonPressed(unsigned int button);
	bool IsButtonReleased(unsigned int button);

	bool IsFocused();
	void LockMouse();
	void ReleaseMouse();
};

#endif