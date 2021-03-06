// FILE: applicationobject.h
// DATE: 3/6/13
// DESC: declaration of the class to manage the application

#ifndef APPLICATIONOBJECT_H
#define APPLICATIONOBJECT_H
#pragma once

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
	virtual bool Draw();
	virtual void Shutdown();

public:
	ApplicationObject();
	ApplicationObject(LPCWSTR name);
	ApplicationObject(const ApplicationObject& application);
	~ApplicationObject();

	void virtual InitializeWindow(int width, int height, const bool& fullscreen) sealed;
	void virtual Run() sealed;
	void virtual ShutdownWindow() sealed;

	LPCWSTR GetName();
	HINSTANCE GetInstance();
	HWND GetWindowHandle();

	bool GetFullscreen();

	LRESULT CALLBACK MessageHandler(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

	static ApplicationObject* Current;
};

static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

#endif;