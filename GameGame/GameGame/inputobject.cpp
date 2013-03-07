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

	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;

	m_mouseX = screenWidth/2;
	m_mouseY = screenHeight/2;

	m_mouseEnabled = true;

	// create input device
	result = DirectInput8Create(instance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_directInput, NULL);
	if (FAILED(result))
		return false;

	// keyboard
	result = m_directInput->CreateDevice(GUID_SysKeyboard, &m_keyboard, NULL);
	if (FAILED(result))
		return false;
	result = m_keyboard->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(result))
		return false;
	result = m_keyboard->SetCooperativeLevel(windowHandle, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
	if (FAILED(result))
		return false;
	result = m_keyboard->Acquire();
	if (FAILED(result))
		return false;

	// mouse
	result = m_directInput->CreateDevice(GUID_SysMouse, &m_mouse, NULL);
	if (FAILED(result))
		return false;
	result = m_mouse->SetDataFormat(&c_dfDIMouse);
	if (FAILED(result))
		return false;
	result = m_mouse->SetCooperativeLevel(windowHandle, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if (FAILED(result))
		return false;
	result = m_mouse->Acquire();
	if (FAILED(result))
		return false;

	return true;
}
bool InputObject::Update()
{
	HRESULT result;

	for (unsigned int i = 0; i < 256; i++)
		m_prevKeyboardState[i] = m_keyboardState[i];

	result = m_keyboard->GetDeviceState(sizeof(m_keyboardState), (LPVOID)&m_keyboardState);
	if (FAILED(result))
	{
		if (result == DIERR_INPUTLOST || result == DIERR_NOTACQUIRED)
			m_keyboard->Acquire();
		else
			return false;
	}

	result = m_mouse->GetDeviceState(sizeof(m_mouseState), (LPVOID)&m_mouseState);
	if (FAILED(result))
	{
		if (result == DIERR_INPUTLOST || result == DIERR_NOTACQUIRED)
			m_mouse->Acquire();
		else
			return false;
	}

	if (m_mouseEnabled)
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
	}

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

bool InputObject::IsKeyTriggered(unsigned long key)
{
	return IsKeyPressed(key) && !IsPrevKeyPressed(key);
}
bool InputObject::IsKeyPressed(unsigned long key)
{
	return m_keyboardState[key] & 0x80;
}
bool InputObject::IsKeyReleased(unsigned long key)
{
	return IsPrevKeyPressed(key) && !IsKeyPressed(key);
}

void InputObject::GetMouseLocation(int& mouseX, int& mouseY)
{
	mouseX = m_mouseX;
	mouseY = m_mouseY;
}

void InputObject::EnableMouseUpdate()
{
	m_mouseEnabled = true;
}
void InputObject::DisableMouseUpdate()
{
	m_mouseEnabled = false;
}

bool InputObject::IsPrevKeyPressed(unsigned long key)
{
	return m_prevKeyboardState[key] & 0x80;
}