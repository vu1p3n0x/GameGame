// FILE: systemclass.cpp
// DATE: 2/21/13 - 2/26/13
// DESC: implementation of the system class to run basic input and output classes

#include "systemclass.h"

SystemClass::SystemClass()
{
	m_Input = NULL;
	m_Graphics = NULL;
}
SystemClass::SystemClass(const SystemClass& systemclass)
{
	m_Input = NULL;
	m_Graphics = NULL;
}

SystemClass::~SystemClass()
{

}

bool SystemClass::Initialize()
{
	int screenWidth, screenHeight;

	screenWidth = 0;
	screenHeight = 0;

	InitializeWindows(screenWidth, screenHeight);

	m_Input = new InputClass;
	if(!m_Input)
		return false;

	m_Input->Initialize();

	m_Graphics = new GraphicsClass;
	if(!m_Graphics)
		return false;

	if(!(m_Graphics->Initialize(screenWidth, screenHeight, m_hwnd)))
		return false;
	
	return true;
}
void SystemClass::Shutdown()
{
	if (m_Input)
	{
		m_Input->Shutdown();
		delete m_Input;
		m_Input = NULL;
	}

	if (m_Graphics)
	{
		m_Graphics->Shutdown();
		delete m_Graphics;
		m_Graphics = NULL;
	}

	ShutdownWindows();
}
void SystemClass::Run()
{
	MSG msg;
	bool done;

	ZeroMemory(&msg, sizeof(MSG));

	done = false;
	while (!done)
	{
		// Handle windows messages
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// stop if quit message or Frame fails
		if (msg.message == WM_QUIT)
			done = true;
		else if (!Frame())
			done = true;
	}
}
bool SystemClass::Frame()
{
	if (m_Input->IsKeyDown(VK_ESCAPE))
		return false;

	if (!(m_Graphics->Frame()))
		return false;

	return true;
}

void SystemClass::InitializeWindows(int& screenWidth, int& screenHeight)
{
	WNDCLASSEX wc;
	DEVMODE dmScreenSettings;
	DWORD ExStyle, Style;
	RECT WindowSize;

	ExStyle = WS_EX_APPWINDOW;
	Style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_POPUP;

	ApplicationHandle = this;

	m_hinstance = GetModuleHandle(NULL);
	m_applicationName = L"GameGame";

	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_hinstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = m_applicationName;
	wc.cbSize = sizeof(WNDCLASSEX);
	
	RegisterClassEx(&wc);

	if(FULL_SCREEN)
	{
		screenWidth  = GetSystemMetrics(SM_CXSCREEN);
		screenHeight = GetSystemMetrics(SM_CYSCREEN);

		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize       = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth  = (unsigned long)screenWidth;
		dmScreenSettings.dmPelsHeight = (unsigned long)screenHeight;
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
		screenWidth  = 1280;
		screenHeight = 720;
		
		WindowSize.left = (GetSystemMetrics(SM_CXSCREEN) - screenWidth)  / 2;
		WindowSize.top = (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2;
		WindowSize.right = WindowSize.left + screenWidth;
		WindowSize.bottom = WindowSize.top + screenHeight;
	}
	
	AdjustWindowRectEx(&WindowSize, Style, FALSE, ExStyle);

	m_hwnd = CreateWindowEx(ExStyle, m_applicationName, m_applicationName, Style, WindowSize.left, WindowSize.top, WindowSize.right-WindowSize.left, WindowSize.bottom-WindowSize.top, NULL, NULL, m_hinstance, NULL);

	ShowWindow(m_hwnd, SW_SHOW);
	SetForegroundWindow(m_hwnd);
	SetFocus(m_hwnd);

	return;
}
void SystemClass::ShutdownWindows()
{
	if(FULL_SCREEN)
		ChangeDisplaySettings(NULL, 0);

	DestroyWindow(m_hwnd);
	m_hwnd = NULL;

	UnregisterClass(m_applicationName, m_hinstance);
	m_hinstance = NULL;

	ApplicationHandle = NULL;

	return;
}

LRESULT CALLBACK SystemClass::MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
	switch(umsg)
	{
	case WM_KEYDOWN:
		m_Input->KeyDown((unsigned int)wparam);
		return 0;
		
	case WM_KEYUP:
		m_Input->KeyUp((unsigned int)wparam);
		return 0;

	default:
		return DefWindowProc(hwnd, umsg, wparam, lparam);

	}
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
			return ApplicationHandle->MessageHandler(hwnd, umessage, wparam, lparam);
	}
}
