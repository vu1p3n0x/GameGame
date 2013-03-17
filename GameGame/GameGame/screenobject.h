// FILE: screenobject.h
// DATE: 3/15/13
// DESC: declaration of the screen object class that will be a base for future screens

#ifndef SCREENOBJECT_H
#define SCREENOBJECT_H

#include "inputobject.h"
#include "graphicsobject.h"

#ifndef SCREENMANAGEROBJECT_H
class ScreenManagerObject;
#endif

class ScreenObject
{
private:
	bool m_requestClose;

protected:
	ScreenManagerObject* m_manager;

	void Close();

public:
	ScreenObject();
	ScreenObject(const ScreenObject&);
	~ScreenObject();

	virtual void Initialize(ScreenManagerObject* manager, GraphicsObject* graphics);
	virtual void Update(InputObject* input, GraphicsObject* graphics) = 0;
	virtual void Draw(GraphicsObject* graphics) = 0;
	virtual void Shutdown();

	bool IsClosing();
};

#include "screenmanagerobject.h"

#endif