// FILE: mainscreen.h
// DATE: 3/16/13
// DESC: declaration of main screen 

#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#pragma comment(lib, "WiltFramework.lib")

#include "WiltFramework.h"
#include "GameScreen.h"

using namespace Wilt;

class MainScreen : public ScreenObject
{
private:
	Text* m_text;
	Font* m_font;

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