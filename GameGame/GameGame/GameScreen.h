// FILE: GameScreen.h
// DATE: 3/16/13
// DESC: 

#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include "screenobject.h"
#include "bitmapobject.h"
#include "textobject.h"

class GameScreen : public ScreenObject
{
	FontObject* font;
	TextObject* text;

	BitmapObject* Cursor;
	float cursorRot;

	BitmapObject* Player;
	float playerPosX;
	float playerPosY;
	float playerVelY;

public:
	GameScreen();
	GameScreen(const GameScreen& gamescreen);
	~GameScreen();

	void Initialize(ScreenManagerObject* manager, GraphicsObject* graphics) override;
	void Update(InputObject* input, GraphicsObject* graphics) override;
	void Draw(GraphicsObject* graphics) override;
	void Shutdown() override;
};

#endif