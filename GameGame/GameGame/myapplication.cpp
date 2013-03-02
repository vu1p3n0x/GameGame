// FILE: myapplication.h
// DATE: 2/26/13
// DESC: implementation of the user created base class

#include "myapplication.h"

MyApplication::MyApplication(LPCWSTR name)
{
	ApplicationObject::ApplicationObject(name);
	m_name = name;

	mytextobject = new TextObject;
	myfontobject = new FontObject;
	mybitmapobject = new BitmapObject;
}

bool MyApplication::Initialize()
{
	thing = 10.0f;

	// set up font
	if (!myfontobject->Initialize(m_graphics->GetD3D()->GetDevice(), "../GameGame/data/fontdata.txt", L"../GameGame/data/font.dds"))
		return false;

	// set up text object
	if (!mytextobject->Initialize(m_graphics, "Herp Derp", 10.0f, 10.0f))
		return false;

	if (!mybitmapobject->Initialize(m_graphics, L"../GameGame/data/seafloor.dds", 256, 256))
		return false;
	
	return true;
}
bool MyApplication::Update()
{
	int x, y;

	m_input->GetMouseLocation(x, y);

	mytextobject->SetPosition(x, y);
	myfontobject->RenderText(m_graphics, mytextobject);

	if (!mybitmapobject->Render(m_graphics, 100, 100))
		return false;

	return true;
}
void MyApplication::Shutdown()
{
	myfontobject->Shutdown();
	mytextobject->Shutdown();
	mybitmapobject->Shutdown();
}