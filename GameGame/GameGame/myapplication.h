// FILE: myapplication.h
// DATE: 3/6/13
// DESC: declaration of the user created base class

#ifndef MYAPPLICATION_H
#define MYAPPLICATION_H

#include "WiltFramework.h"
#include "mainscreen.h"

class MyApplication : public ApplicationObject
{
private:
	ScreenManagerObject* ScreenManager;

public:
	MyApplication(LPCWSTR name);

	bool Initialize();
	bool Update();
	bool Draw();
	void Shutdown();
};

#endif