// FILE: screenmanagerobject.h
// DATE: 3/15/13
// DESC: declaration of the screen manager object to manage screen object

#ifndef SCREENMANAGEROBJECT_H
#define SCREENMANAGEROBJECT_H

#include <stack>

#include "inputobject.h"
#include "graphicsobject.h"

#ifndef SCREENOBJECT_H
class ScreenObject;
#endif

class ScreenManagerObject
{
private:
	std::stack<ScreenObject*>* m_stack;
	ScreenObject* m_next;

public:
	ScreenManagerObject();
	ScreenManagerObject(const ScreenManagerObject& screenmanager);
	~ScreenManagerObject();

	void Initialize(ScreenObject* screen);
	void Update(InputObject* input, GraphicsObject* graphics);
	void Draw(GraphicsObject* graphics);
	void Shutdown();

	void SetNextScreen(ScreenObject* screen);
};

#include "screenobject.h"

#endif