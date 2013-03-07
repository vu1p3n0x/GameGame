// FILE: myapplication.h
// DATE: 3/6/13
// DESC: declaration of the user created base class

#ifndef MYAPPLICATION_H
#define MYAPPLICATION_H

#include "applicationobject.h"
#include "fontobject.h"
#include "textobject.h"
#include "bitmapobject.h"

class MyApplication : public ApplicationObject
{
private:
	FontObject* myfontobject;
	TextObject* mytextobject;

	BitmapObject* Cursor;

	BitmapObject* Player;
	float playerPosX;
	float playerPosY;
	float playerVelY;

	float thing;
	bool focus;

public:
	MyApplication(LPCWSTR name);

	bool Initialize();
	bool Update();
	void Shutdown();
};

static MyApplication* AppObject = NULL;

#endif