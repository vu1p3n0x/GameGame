// FILE: inputobject.cpp
// DATE: 3/6/13
// DESC: implementation of an object to manage external input

#include "inputobject.h"

InputObject::InputObject()
{
	m_directInput = NULL;
	m_keyboard = NULL;
	m_mouse = NULL;
}
InputObject::InputObject(const InputObject& inputobject)
{
	m_directInput = NULL;
	m_keyboard = NULL;
	m_mouse = NULL;
}
InputObject::~InputObject()
{
	if (m_mouse)
	{
		m_mouse->Unacquire();
		m_mouse->Release();
		m_mouse = NULL;
	}

	if (m_keyboard)
	{
		m_keyboard->Unacquire();
		m_keyboard->Release();
		m_keyboard = NULL;
	}

	if (m_directInput)
	{
		m_directInput->Release();
		m_directInput = NULL;
	}
}

bool InputObject::Initialize(HINSTANCE instance, HWND windowHandle, int screenWidth, int screenHeight)
{
	HRESULT result;

	m_hwnd = windowHandle;

	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;

	m_mouseX = screenWidth/2;
	m_mouseY = screenHeight/2;

	m_mouseLocked = true;
	ShowCursor(false);

	// create input device
	result = DirectInput8Create(instance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_directInput, NULL);
	if (FAILED(result))
		throw std::exception("Failed to create the DirectInput object");

	// keyboard
	result = m_directInput->CreateDevice(GUID_SysKeyboard, &m_keyboard, NULL);
	if (FAILED(result))
		throw std::exception("Failed to create the keyboard device");
	result = m_keyboard->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(result))
		throw std::exception("Failed to set the keyboard data format");
	result = m_keyboard->SetCooperativeLevel(windowHandle, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
	if (FAILED(result))
		throw std::exception("Failed to set the keyboard cooperative level");
	result = m_keyboard->Acquire();
	if (FAILED(result))
		throw std::exception("Failed to acquire the keyboard");

	// mouse
	result = m_directInput->CreateDevice(GUID_SysMouse, &m_mouse, NULL);
	if (FAILED(result))
		throw std::exception("Failed to create the mouse device");
	result = m_mouse->SetDataFormat(&c_dfDIMouse);
	if (FAILED(result))
		throw std::exception("Failed to set the mouse data format");
	result = m_mouse->SetCooperativeLevel(windowHandle, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if (FAILED(result))
		throw std::exception("Failed to set the mouse cooperative level");
	result = m_mouse->Acquire();
	if (FAILED(result))
		throw std::exception("Failed to acquire the mouse");

	return true;
}
bool InputObject::Update()
{
	HRESULT result;

	m_prevMouseState = m_mouseState;
	for (unsigned int i = 0; i < 256; i++)
		m_prevKeyboardState[i] = m_keyboardState[i];

	result = m_mouse->GetDeviceState(sizeof(m_mouseState), (LPVOID)&m_mouseState);
	if (FAILED(result))
	{
		if (result == DIERR_INPUTLOST || result == DIERR_NOTACQUIRED)
			m_mouse->Acquire();
		else
			throw std::exception("Failed to get the mouse state");
	}

	result = m_keyboard->GetDeviceState(sizeof(m_keyboardState), (LPVOID)&m_keyboardState);
	if (FAILED(result))
	{
		if (result == DIERR_INPUTLOST || result == DIERR_NOTACQUIRED)
			m_keyboard->Acquire();
		else
			throw std::exception("Failed to get the keyboard state");
	}

	if (GetFocus() == m_hwnd)
	{
		if (m_mouseLocked)
		{
			m_mouseX += m_mouseState.lX;
			m_mouseY -= m_mouseState.lY;

			if (m_mouseX < 0)  
				m_mouseX = 0;
			if (m_mouseY < 0)
				m_mouseY = 0;

			if (m_mouseX > m_screenWidth)
				m_mouseX = m_screenWidth;
			if (m_mouseY > m_screenHeight)
				m_mouseY = m_screenHeight; 

			RECT position;
			GetWindowRect(m_hwnd, &position);
			SetCursorPos((position.right + position.left)/2, (position.bottom + position.top)/2);
		}
	}
	else if (m_mouseLocked)
		ReleaseMouse();

	return true;
}
void InputObject::Shutdown()
{
	if (m_mouse)
	{
		m_mouse->Unacquire();
		m_mouse->Release();
		m_mouse = NULL;
	}

	if (m_keyboard)
	{
		m_keyboard->Unacquire();
		m_keyboard->Release();
		m_keyboard = NULL;
	}

	if (m_directInput)
	{
		m_directInput->Release();
		m_directInput = NULL;
	}
}

bool InputObject::IsKeyTriggered(unsigned int key)
{
	if (key >= INPUTOBJECT_KEYBOARD_MAX)
		throw std::exception("Keyboard key index out of bounds");
	if (IsFocused() || GetFocus()==m_hwnd)
		return (IsKeyPressed(key) && !IsPrevKeyPressed(key)) != 0;
	return false;
}
bool InputObject::IsKeyPressed(unsigned int key)
{
	if (key >= INPUTOBJECT_KEYBOARD_MAX)
		throw std::exception("Keyboard key index out of bounds");
	if (IsFocused() || GetFocus()==m_hwnd)
		return (m_keyboardState[key] & 0x80) != 0;
	return false;
}
bool InputObject::IsKeyReleased(unsigned int key)
{
	if (key >= INPUTOBJECT_KEYBOARD_MAX)
		throw std::exception("Keyboard key index out of bounds");
	if (IsFocused() || GetFocus()==m_hwnd)
		return (IsPrevKeyPressed(key) && !IsKeyPressed(key)) != 0;
	return false;
}

void InputObject::GetMouseLocation(int& mouseX, int& mouseY)
{
	mouseX = m_mouseX;
	mouseY = m_mouseY;
}
bool InputObject::IsFocused()
{
	return m_mouseLocked;
}

bool InputObject::IsButtonTriggered(unsigned int button)
{
	if (button >= INPUTOBJECT_MOUSE_MAX)
		throw std::exception("Mouse button index out of bounds");
	if (IsFocused())
		return (IsButtonPressed(button) && !IsPrevButtonPressed(button)) != 0;
	return false;
}
bool InputObject::IsButtonPressed(unsigned int button)
{
	if (button >= INPUTOBJECT_MOUSE_MAX)
		throw std::exception("Mouse button index out of bounds");
	if (IsFocused())
		return (m_mouseState.rgbButtons[button] & 0x80) != 0;
	return false;
}
bool InputObject::IsButtonReleased(unsigned int button)
{
	if (button >= INPUTOBJECT_MOUSE_MAX)
		throw std::exception("Mouse button index out of bounds");
	if (IsFocused())
		return (IsPrevButtonPressed(button) && !IsButtonPressed(button)) != 0;
	return false;
}

void InputObject::LockMouse()
{
	if (!m_mouseLocked)
	{
		ShowCursor(false);
		m_mouseLocked = true;
	}
}
void InputObject::ReleaseMouse()
{
	if (m_mouseLocked)
	{
		ShowCursor(true);
		m_mouseLocked = false; 
	}
}

bool InputObject::IsPrevKeyPressed(unsigned int key)
{
	return (m_prevKeyboardState[key] & 0x80) != 0;
}
bool InputObject::IsPrevButtonPressed(unsigned int button)
{
	return (m_prevMouseState.rgbButtons[button] & 0x80) != 0;
}