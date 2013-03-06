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

	Cursor = new BitmapObject;
	Player = new BitmapObject;

	NewThing = new BitmapObject2;
}

bool MyApplication::Initialize()
{
	thing = 0.0f;
	focus = true;

	playerPosX = 0.0f;
	playerPosY = 0.0f;
	playerVelY = 0.0f;

	// set up font
	if (!myfontobject->Initialize(m_graphics->GetD3D()->GetDevice(), "../GameGame/data/fontdata.txt", L"../GameGame/data/font.dds"))
		return false;

	// set up text object
	if (!mytextobject->Initialize(m_graphics, "Herp Derp", 10.0f, 10.0f))
		return false;

	if (!Cursor->Initialize(m_graphics, L"../GameGame/data/target.png", 512, 512))
		return false;
	Cursor->SetScale(0.125f);

	if (!Player->Initialize(m_graphics, L"../GameGame/data/ball.png", 256, 256))
		return false;
	Player->SetScale(0.5);

	if (!NewThing->Initialize(m_graphics, L"../GameGame/data/ball.png", 256, 256))
		return false;
	NewThing->SetPosition(400, 400);
	NewThing->SetScale(0.5f);
	NewThing->SetOrigin(0.5, 0.5f);

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

	playerVelY -= 1.0f;
	playerPosY += playerVelY;
	
	if (playerPosY < 0.0f)
	{
		playerPosY = 0.0f;
		playerVelY = 0.0f;
	}

	if (m_input->IsKeyPressed(DIK_SPACE) && playerPosY == 0.0f)
		playerVelY = 30.0f;

	if (m_input->IsKeyPressed(DIK_A))
		playerPosX -= 5.0f;
	if (m_input->IsKeyPressed(DIK_D))
		playerPosX += 5.0f;

	

	m_input->GetMouseLocation(x, y); 
	
	mytextobject->SetPosition(10, 10);
	myfontobject->RenderText(m_graphics, mytextobject);

	Cursor->SetPosition(x + 45.255f*cos(thing), y + 45.255f*sin(thing));
	Cursor->SetRotation(-1 * thing - 1.57079632679f - 0.78539816339f);
	if (!Cursor->Render(m_graphics))
		return false;

	Player->SetPosition(playerPosX + 64, m_graphics->GetScreenHeight() - (playerPosY + 128));
	Player->Render(m_graphics);
	
	NewThing->SetRotation(thing);
	NewThing->Render(m_graphics);

	return true;
}

void MyApplication::Shutdown()
{
	myfontobject->Shutdown();
	mytextobject->Shutdown();
	Cursor->Shutdown();
}