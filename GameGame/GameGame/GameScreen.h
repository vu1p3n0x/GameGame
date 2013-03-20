// FILE: GameScreen.h
// DATE: 3/16/13
// DESC: 

#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#pragma comment(lib, "WiltFramework.lib")

#include "WiltFramework.h"

using namespace Wilt;

class GameScreen : public ScreenObject
{
	Font* font;
	Text* text;

	Bitmap* Cursor;
	float cursorRot;

	Bitmap* Player;
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