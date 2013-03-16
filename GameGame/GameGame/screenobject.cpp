// FILE: screenobject.cpp
// DATE: 3/15/13
// DESC: implementation of the screen object class that will be a base for future screens

#include "screenobject.h"

ScreenObject::ScreenObject()
{
	m_manager = NULL;
	m_requestClose = false;
}
ScreenObject::ScreenObject(const ScreenObject& screen)
{
	m_manager = NULL;
	m_requestClose = false;
}
ScreenObject::~ScreenObject()
{

}

void ScreenObject::Initialize(ScreenManagerObject* manager)
{
	m_manager = manager;
	m_requestClose = false;
}
void ScreenObject::Update(InputObject* input)
{

}
void ScreenObject::Draw(GraphicsObject* graphics)
{

}
void ScreenObject::Shutdown()
{
	if (m_manager)
		m_manager = NULL;
}

bool ScreenObject::IsClosing()
{
	return m_requestClose;
}

void ScreenObject::Close()
{
	m_requestClose = true;
}