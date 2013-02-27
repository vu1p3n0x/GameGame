// FILE: myapplication.h
// DATE: 2/26/13
// DESC: declaration of the user created base class

#ifndef MYAPPLICATION_H
#define MYAPPLICATION_H

#include "applicationobject.h"

class MyApplication : public ApplicationObject
{
public:
	MyApplication(LPCWSTR name);

	bool Initialize();
	bool Update();
};

static MyApplication* AppObject = NULL;

#endif