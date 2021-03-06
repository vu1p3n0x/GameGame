// FILE: main.cpp
// DATE: 2/21/13 - 2/26/13
// DESC: Entry function for application

#pragma comment(lib, "WiltFramework.lib")

#include "myapplication.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	MyApplication* app = new MyApplication(L"TestGame");
	if (!app)
		return 0;
	ApplicationObject::Current = app;

	app->InitializeWindow(1280, 720, false);
	app->Run();
	app->ShutdownWindow();

	delete app;
	app = NULL;

	return 0;
}