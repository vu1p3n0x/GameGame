// FILE: myapplication.h
// DATE: 2/26/13
// DESC: implementation of the user created base class

#include "myapplication.h"

MyApplication::MyApplication(LPCWSTR name)
{
	ApplicationObject::ApplicationObject(name);
	m_name = name;

	mytextobject = NULL;
	myfontobject = NULL;
}

bool MyApplication::Initialize()
{
	myfontobject = new FontObject(m_graphics->GetD3D()->GetDevice(), "../GameGame/data/fontdata.txt", L"../GameGame/data/font.dds");
	mytextobject = new TextObject(m_graphics, "Test1", 10.0f, 10.0f);
	
	return true;
}
bool MyApplication::Update()
{
	mytextobject->SetText("Test2 ... did it work?");
	mytextobject->SetPosition(10.0f, 10.0f);
	myfontobject->RenderText(m_graphics, mytextobject);
	return true;
}