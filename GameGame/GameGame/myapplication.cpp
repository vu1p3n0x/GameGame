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
	thing = 0.0f;
	focus = true;

	// set up font
	if (!myfontobject->Initialize(m_graphics->GetD3D()->GetDevice(), "../GameGame/data/fontdata.txt", L"../GameGame/data/font.dds"))
		return false;

	// set up text object
	if (!mytextobject->Initialize(m_graphics, "Herp Derp", 10.0f, 10.0f))
		return false;

	if (!mybitmapobject->Initialize(m_graphics, L"../GameGame/data/target.png", 512, 512))
		return false;

	ShowCursor(false);
	
	return true;
}

bool MyApplication::Update()
{
	int x, y;
	RECT position;

	thing += 0.05f;

	if(m_input->IsKeyTriggered(DIK_ESCAPE))
	{
		if (focus)
		{
			focus = false;
			ShowCursor(true);
			m_input->DisableMouseUpdate();
		}
		else
		{
			focus = true;
			ShowCursor(false);
			m_input->EnableMouseUpdate();
		}
	}
	
	if (focus)
	{
		GetWindowRect(m_hwnd, &position);
		if (GetFocus() == m_hwnd)
			SetCursorPos((position.right + position.left)/2, (position.bottom + position.top)/2);
	}
	
	m_input->GetMouseLocation(x, y); 
	
	mytextobject->SetPosition(10, 10);
	myfontobject->RenderText(m_graphics, mytextobject);

	mybitmapobject->SetPosition(x + 45.255f*cos(thing), y + 45.255f*sin(thing));
	mybitmapobject->SetRotation(-1 * thing - 1.57079632679f - 0.78539816339f);
	mybitmapobject->SetScale(0.125f);
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