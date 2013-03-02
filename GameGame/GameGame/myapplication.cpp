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
	RECT position;

	ShowCursor(false);

	GetWindowRect(m_hwnd, &position);
	if (GetFocus() == m_hwnd)
		SetCursorPos((position.right + position.left)/2, (position.bottom + position.top)/2);

	m_input->GetMouseLocation(x, y);

	mytextobject->SetPosition(x, y);
	myfontobject->RenderText(m_graphics, mytextobject);

	mybitmapobject->SetPosition(100, 100);
	mybitmapobject->SetScale(0.5f, 1.0f);
	if (!mybitmapobject->Render(m_graphics))
		return false;

	return true;
}

void MyApplication::Shutdown()
{
	myfontobject->Shutdown();
	mytextobject->Shutdown();
	mybitmapobject->Shutdown();
}