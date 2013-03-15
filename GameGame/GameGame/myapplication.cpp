// FILE: myapplication.h
// DATE: 3/6/13
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
}

bool MyApplication::Initialize()
{
	m_graphics->GetD3D()->TurnOnAlphaBlending();

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

	Cursor->Initialize(m_graphics, L"../GameGame/data/target.png", 512, 512);
	Cursor->SetOrigin(0.5f, 0.5f);
	Cursor->SetScale(0.125f);

	Player->Initialize(m_graphics, L"../GameGame/data/ball.png", 256, 256);
	Player->SetOrigin(0.5f, 0.5f);
	Player->SetScale(0.5);
	
	return true;
}

bool MyApplication::Update()
{
	int x, y;
	RECT position;

	thing += 0.05f;

	if(m_input->IsKeyTriggered(DIK_ESCAPE))
	{
		if (m_input->IsFocused())
			m_input->ReleaseMouse();
		else
			m_input->LockMouse();
	}

	playerVelY -= 1.0f;

	if (m_input->IsKeyPressed(DIK_SPACE) && playerPosY == 0.0f)
		playerVelY = 30.0f;
	if (m_input->IsButtonPressed(0))
		playerVelY = 0.0f;

	if (m_input->IsKeyPressed(DIK_A))
		playerPosX -= 5.0f;
	if (m_input->IsKeyPressed(DIK_D))
		playerPosX += 5.0f;

	playerPosY += playerVelY;
	
	if (playerPosY < 0.0f)
	{
		playerPosY = 0.0f;
		playerVelY = 0.0f;
	}

	m_input->GetMouseLocation(x, y); 
	
	mytextobject->SetPosition(10, 10);
	myfontobject->RenderText(m_graphics, mytextobject);

	Cursor->SetPosition(x, y);
	Cursor->SetRotation(thing);
	Cursor->Render(m_graphics);

	Player->SetPosition(playerPosX, playerPosY + 64);
	Player->Render(m_graphics);

	return true;
}

void MyApplication::Shutdown()
{
	m_graphics->GetD3D()->TurnOffAlphaBlending();

	myfontobject->Shutdown();
	mytextobject->Shutdown();
	Cursor->Shutdown();
}