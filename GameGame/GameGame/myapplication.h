// FILE: myapplication.h
// DATE: 2/26/13
// DESC: declaration of the user created base class

#ifndef MYAPPLICATION_H
#define MYAPPLICATION_H

#include "applicationobject.h"
#include "fontobject.h"
#include "textobject.h"

class MyApplication : public ApplicationObject
{
private:
	FontObject* myfontobject;
	TextObject* mytextobject;
	float thing;

public:
	MyApplication(LPCWSTR name);

	bool Initialize();
	bool Update();
	void Shutdown();
};

static MyApplication* AppObject = NULL;

#endif