// FILE: systemclass.h
// DATE: 2/21/13
// DESC: declaration of the system class to run basic input and output classes

#ifndef SYSTEMCLASS_H
#define SYSTEMCLASS_H

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "inputclass.h"
#include "graphicsclass.h"

class SystemClass
{
public:
	SystemClass();
	SystemClass(const SystemClass&);
	~SystemClass();

	bool Initialize();
	void Run();
	void Shutdown();

	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

private:
	LPCWSTR m_applicationName;
	HINSTANCE m_hinstance;
	HWND m_hwnd;

	InputClass* m_Input;
	GraphicsClass* m_Graphics;

	bool Frame();
	void InitializeWindows(int&, int&);
	void ShutdownWindows();
};

static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
static SystemClass* ApplicationHandle = NULL;

#endif