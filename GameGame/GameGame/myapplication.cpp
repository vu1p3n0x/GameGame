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
	thing = 10.0f;
}

bool MyApplication::Initialize()
{
	myfontobject = new FontObject(m_graphics->GetD3D()->GetDevice(), "../GameGame/data/fontdata.txt", L"../GameGame/data/font.dds");
	mytextobject = new TextObject(m_graphics, "Herp Derp", 10.0f, 10.0f);
	
	return true;
}
bool MyApplication::Update()
{
	thing += 1.0f;
	mytextobject->SetPosition(10.0f, thing);
	myfontobject->RenderText(m_graphics, mytextobject);

	return true;
}