// FILE: myapplication.h
// DATE: 3/6/13
// DESC: implementation of the user created base class

#include "myapplication.h"

MyApplication::MyApplication(LPCWSTR name)
{
	ApplicationObject::ApplicationObject(name);
	m_name = name;

	ScreenManager = new ScreenManagerObject;
}

bool MyApplication::Initialize()
{
	m_graphics->GetD3D()->TurnOnAlphaBlending();
	m_graphics->GetD3D()->TurnZBufferOff();

	MainScreen* mainScreen = new MainScreen;
	mainScreen->Initialize(ScreenManager, m_graphics);
	ScreenManager->Initialize(mainScreen);
	
	return true;
}

bool MyApplication::Update()
{
	if(m_input->IsKeyTriggered(DIK_ESCAPE))
	{
		if (m_input->IsFocused())
			m_input->ReleaseMouse();
		else
			m_input->LockMouse();
	}

	ScreenManager->Update(m_input, m_graphics);

	return true;
}
bool MyApplication::Draw()
{
	ScreenManager->Draw(m_graphics);
	
	return true;
}

void MyApplication::Shutdown()
{
	m_graphics->GetD3D()->TurnZBufferOn();
	m_graphics->GetD3D()->TurnOffAlphaBlending();

	ScreenManager->Shutdown();
}