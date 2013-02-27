// FILE: applicationobject.h
// DATE: 2/26/13
// DESC: declaration of the class to manage the application

#ifndef APPLICATIONOBJECT_H
#define APPLICATIONOBJECT_H

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

class ApplicationObject
{
private:
	LPCWSTR   m_name;
	HINSTANCE m_instance;
	HWND      m_hwnd;

protected:
	virtual bool Initialize();
	virtual bool Update();

public:
	ApplicationObject(LPCWSTR name);
	ApplicationObject(const ApplicationObject& application);
	~ApplicationObject();

	void InitializeWindow(int width, int height, const bool& fullscreen);
	void Run();
	void ShutdownWindow();

	LPCWSTR GetName();
	HINSTANCE GetInstance();
	HWND GetWindowHandle();

	LRESULT CALLBACK MessageHandler(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
};

static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
static ApplicationObject* AppObject = NULL;

#endif;