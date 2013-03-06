// FILE: myapplication.h
// DATE: 2/26/13
// DESC: declaration of the user created base class

#ifndef MYAPPLICATION_H
#define MYAPPLICATION_H

#include "applicationobject.h"
#include "fontobject.h"
#include "textobject.h"
#include "bitmapobject.h"
#include "bitmapobject2.h"

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

	BitmapObject2* NewThing;

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