// FILE: screenmanagerobject.cpp
// DATE: 3/15/13
// DESC: implementation of the screen manager object to manage screen object

#include "screenmanagerobject.h"

ScreenManagerObject::ScreenManagerObject(void)
{
	m_stack = NULL;
	m_next = NULL;
}
ScreenManagerObject::ScreenManagerObject(const ScreenManagerObject& screenmanager)
{
	m_stack = NULL;
	m_next = NULL;
}
ScreenManagerObject::~ScreenManagerObject(void)
{
	if (m_stack)
	{
		while (m_stack->size() > 0)
		{
			ScreenObject* screen = m_stack->top();
			m_stack->pop();

			screen->Shutdown();
			delete screen;
		}
		delete m_stack;
		m_stack = NULL;
	}

	if (m_next)
	{
		m_next->Shutdown();
		delete m_next;
		m_next = NULL;
	}
}

void ScreenManagerObject::Initialize(ScreenObject* screen)
{
	m_stack = new std::stack<ScreenObject*>();
	m_stack->push(screen);
}
void ScreenManagerObject::Update(InputObject* input, GraphicsObject* graphics)
{
	if (m_stack->size() == 0)
		return;

	if (m_stack->top()->IsClosing())
	{
		m_stack->top()->Shutdown();
		delete m_stack->top();
		m_stack->pop();
	}

	if (m_next)
	{
		m_stack->push(m_next);
		m_next = NULL;
	}
	
	m_stack->top()->Update(input, graphics);
}
void ScreenManagerObject::Draw(GraphicsObject* graphics)
{
	if (m_stack->size() == 0)
		return;

	m_stack->top()->Draw(graphics);
}
void ScreenManagerObject::Shutdown()
{
	if (m_stack)
	{
		while (m_stack->size() > 0)
		{
			ScreenObject* screen = m_stack->top();
			m_stack->pop();

			screen->Shutdown();
			delete screen;
		}
		delete m_stack;
		m_stack = NULL;
	}

	if (m_next)
	{
		m_next->Shutdown();
		delete m_next;
		m_next = NULL;
	}
}

void ScreenManagerObject::SetNextScreen(ScreenObject* screen)
{
	m_next = screen;
}