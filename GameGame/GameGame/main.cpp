// FILE: main.cpp
// DATE: 2/21/13
// DESC: Entry function for application

#include "systemclass.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	SystemClass* system;

	system = new SystemClass;
	if (!system)
		return 0;

	if (system->Initialize())
		system->Run();

	system->Shutdown();
	delete system;
	system = NULL;

	return 0;
}