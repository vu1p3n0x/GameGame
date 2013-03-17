// FILE: mainscreen.h
// DATE: 3/16/13
// DESC: declaration of main screen 

#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include "screenobject.h"
#include "textobject.h"

class MainScreen : public ScreenObject
{
private:
	TextObject* m_text;
	FontObject* m_font;

public:
	MainScreen();
	MainScreen(const MainScreen& mainscreen);
	~MainScreen();

	void Initialize(ScreenManagerObject* manager, GraphicsObject* graphics) override;
	void Update(InputObject* input, GraphicsObject* graphics) override;
	void Draw(GraphicsObject* graphics) override;
	void Shutdown() override;
};

#endif