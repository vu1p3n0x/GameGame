// FILE: applicationobject.cpp
// DATE: 2/26/13
// DESC: implementation of the class to manage the application

#include "applicationobject.h"
#include "myapplication.h"

ApplicationObject::ApplicationObject()
{
	m_instance = GetModuleHandle(NULL);
	m_name = L"Game";
}
ApplicationObject::ApplicationObject(LPCWSTR name)
{
	m_instance = GetModuleHandle(NULL);
	m_name = name;
}
ApplicationObject::ApplicationObject(const ApplicationObject& application)
{

}
ApplicationObject::~ApplicationObject()
{

}

void ApplicationObject::InitializeWindow(int width, int height, const bool& fullscreen)
{
	WNDCLASSEX wc;
	DEVMODE dmScreenSettings;
	DWORD ExStyle, Style;
	RECT WindowSize;

	ExStyle = WS_EX_APPWINDOW;
	Style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_POPUP;

	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_instance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = m_name;
	wc.cbSize = sizeof(WNDCLASSEX);
	
	RegisterClassEx(&wc);

	if(fullscreen)
	{
		width  = GetSystemMetrics(SM_CXSCREEN);
		height = GetSystemMetrics(SM_CYSCREEN);

		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize       = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth  = (unsigned long)width;
		dmScreenSettings.dmPelsHeight = (unsigned long)height;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields     = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

		WindowSize.left = 0;
		WindowSize.top = 0;
		WindowSize.right = GetSystemMetrics(SM_CXSCREEN);
		WindowSize.bottom = GetSystemMetrics(SM_CYSCREEN);
	}
	else
	{
		width  = 1280;
		height = 720;
		
		WindowSize.left = (GetSystemMetrics(SM_CXSCREEN) - width)  / 2;
		WindowSize.top = (GetSystemMetrics(SM_CYSCREEN) - height) / 2;
		WindowSize.right = WindowSize.left + width;
		WindowSize.bottom = WindowSize.top + height;
	}

	m_fullscreen = fullscreen;
	m_width = width;
	m_height = height;
	
	AdjustWindowRectEx(&WindowSize, Style, FALSE, ExStyle);
	m_hwnd = CreateWindowEx(ExStyle, m_name, m_name, Style, WindowSize.left, WindowSize.top, WindowSize.right-WindowSize.left, WindowSize.bottom-WindowSize.top, NULL, NULL, m_instance, NULL);

	ShowWindow(m_hwnd, SW_SHOW);
	SetForegroundWindow(m_hwnd);
	SetFocus(m_hwnd);

	m_graphics = new GraphicsObject(m_hwnd, m_width, m_height, m_fullscreen);

	return;
}
void ApplicationObject::Run()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	if (!Initialize())
		return;

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (msg.message == WM_QUIT)
			return;

		if (!Update())
			return;
	}
}
void ApplicationObject::ShutdownWindow()
{
	/*if(graphics->fullscreen)
		ChangeDisplaySettings(NULL, 0);*/

	DestroyWindow(m_hwnd);
	m_hwnd = NULL;

	UnregisterClass(m_name, m_instance);
	m_instance = NULL;

	AppObject = NULL;
}

LPCWSTR ApplicationObject::GetName()
{
	return m_name;
}
HINSTANCE ApplicationObject::GetInstance()
{
	return m_instance;
}

int ApplicationObject::GetWidth()
{
	return m_width;
}
int ApplicationObject::GetHeight()
{
	return m_height;
}
bool ApplicationObject::GetFullscreen()
{
	return m_fullscreen;
}

GraphicsObject* ApplicationObject::GetGraphicsObject()
{
	return m_graphics;
}

LRESULT CALLBACK ApplicationObject::MessageHandler(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch(msg)
	{
	case WM_KEYDOWN:
		// m_Input->KeyDown((unsigned int)wparam);
		return 0;
		
	case WM_KEYUP:
		// m_Input->KeyUp((unsigned int)wparam);
		return 0;

	default:
		return DefWindowProc(hwnd, msg, wparam, lparam);

	}
}

bool ApplicationObject::Initialize()
{
	return true;
}
bool ApplicationObject::Update()
{
	return true;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
{
	switch(umessage)
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;

		case WM_CLOSE:
			PostQuitMessage(0);		
			return 0;

		default:
			return AppObject->MessageHandler(hwnd, umessage, wparam, lparam);
	}
}