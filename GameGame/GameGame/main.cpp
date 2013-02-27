// FILE: main.cpp
// DATE: 2/21/13
// DESC: Entry function for application

#include "applicationobject.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	ApplicationObject* app = new ApplicationObject(L"TestGane");
	if (!app)
		return 0;

	app->InitializeWindow(1280, 720, false);
	app->Run();
	app->ShutdownWindow();

	delete app;
	app = NULL;

	return 0;
}

//#include "systemclass.h"
//
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
//{
//	SystemClass* system;
//
//	system = new SystemClass;
//	if (!system)
//		return 0;
//
//	if (system->Initialize())
//		system->Run();
//
//	system->Shutdown();
//	delete system;
//	system = NULL;
//
//	return 0;
//}