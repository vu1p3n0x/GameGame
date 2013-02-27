// FILE: myapplication.h
// DATE: 2/26/13
// DESC: implementation of the user created base class

#include "myapplication.h"

MyApplication::MyApplication(LPCWSTR name)
{
	ApplicationObject::ApplicationObject(name);
}

bool MyApplication::Initialize()
{
	return true;
}
bool MyApplication::Update()
{
	return true;
}