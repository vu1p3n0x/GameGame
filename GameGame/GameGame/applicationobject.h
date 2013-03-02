// FILE: applicationobject.h
// DATE: 2/26/13
// DESC: declaration of the class to manage the application

#ifndef APPLICATIONOBJECT_H
#define APPLICATIONOBJECT_H

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "graphicsobject.h"
#include "inputobject.h"

class ApplicationObject
{
protected:
	LPCWSTR   m_name;
	HINSTANCE m_instance;
	HWND      m_hwnd;

	int m_width;
	int m_height;
	bool m_fullscreen;

	GraphicsObject* m_graphics;
	InputObject* m_input;

protected:
	virtual bool Initialize();
	virtual bool Update();
	virtual void Shutdown();

public:
	ApplicationObject();
	ApplicationObject(LPCWSTR name);
	ApplicationObject(const ApplicationObject& application);
	~ApplicationObject();

	void InitializeWindow(int width, int height, const bool& fullscreen);
	void Run();
	void ShutdownWindow();

	LPCWSTR GetName();
	HINSTANCE GetInstance();

	int GetWidth();
	int GetHeight();
	bool GetFullscreen();

	GraphicsObject* GetGraphicsObject();

	LRESULT CALLBACK MessageHandler(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
};

static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

#endif;