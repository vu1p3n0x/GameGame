// FILE: myapplication.h
// DATE: 2/26/13
// DESC: implementation of the user created base class

#include "myapplication.h"

MyApplication::MyApplication(LPCWSTR name)
{
	ApplicationObject::ApplicationObject(name);
	m_name = name;
	mytextobject = NULL;
}

bool MyApplication::Initialize()
{
	mytextobject = new TextObject(m_graphics, "Test1", 100.0f, 100.0f);
	return true;
}
bool MyApplication::Update()
{
	return true;
}