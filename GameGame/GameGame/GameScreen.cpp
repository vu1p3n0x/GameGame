#include "GameScreen.h"

GameScreen::GameScreen()
{
	font = new FontObject;
	text = new TextObject;

	Cursor = new BitmapObject;
	Player = new BitmapObject;
}
GameScreen::GameScreen(const GameScreen& gamescreen)
{
	font = new FontObject;
	text = new TextObject;

	Cursor = new BitmapObject;
	Player = new BitmapObject;
}
GameScreen::~GameScreen()
{
	if (font)
	{
		font->Shutdown();
		delete font;
		font = NULL;
	}
	if (text)
	{
		text->Shutdown();
		delete text;
		text = NULL;
	}

	if (Cursor)
	{
		Cursor->Shutdown();
		delete Cursor;
		Cursor = NULL;
	}
	if (Player)
	{
		Player->Shutdown();
		delete Player;
		Player = NULL;
	}
}

void GameScreen::Initialize(ScreenManagerObject* manager, GraphicsObject* graphics)
{
	font->Initialize(graphics->GetD3D()->GetDevice(), "../GameGame/data/fontdata.txt", L"../GameGame/data/font.dds");
	text->Initialize(graphics, "Game Menu", 10, 10);

	cursorRot = 0.0f;

	playerPosX = 0.0f;
	playerPosY = 0.0f;
	playerVelY = 0.0f;

	Cursor->Initialize(graphics, L"../GameGame/data/target.png", 512, 512);
	Cursor->SetOrigin(0.5f, 0.5f);
	Cursor->SetScale(0.125f);

	Player->Initialize(graphics, L"../GameGame/data/ball.png", 256, 256);
	Player->SetOrigin(0.5f, 0.5f);
	Player->SetScale(0.5);
}
void GameScreen::Update(InputObject* input, GraphicsObject* graphics)
{
	int x, y;
	cursorRot += 0.05f;

	playerVelY -= 1.0f;

	if (input->IsFocused())
	{
		if (input->IsKeyPressed(DIK_SPACE) && playerPosY == 0.0f)
			playerVelY = 30.0f;
		if (input->IsButtonPressed(0))
			playerVelY = 0.0f;
		
		if (input->IsKeyPressed(DIK_A))
			playerPosX -= 5.0f;
		if (input->IsKeyPressed(DIK_D))
			playerPosX += 5.0f; 

		if (input->IsButtonTriggered(1))
			Close();
	}

	playerPosY += playerVelY;
	
	if (playerPosY < 0.0f)
	{
		playerPosY = 0.0f;
		playerVelY = 0.0f;
	}

	input->GetMouseLocation(x, y); 
	
	Cursor->SetPosition(x, y);
	Cursor->SetRotation(cursorRot);

	Player->SetPosition(playerPosX, playerPosY + 64);
}
void GameScreen::Draw(GraphicsObject* graphics)
{
	font->RenderText(graphics, text);

	Cursor->Render(graphics);
	Player->Render(graphics);
}
void GameScreen::Shutdown()
{
	if (font)
	{
		font->Shutdown();
		delete font;
		font = NULL;
	}
	if (text)
	{
		text->Shutdown();
		delete text;
		text = NULL;
	}

	if (Cursor)
	{
		Cursor->Shutdown();
		delete Cursor;
		Cursor = NULL;
	}
	if (Player)
	{
		Player->Shutdown();
		delete Player;
		Player = NULL;
	}
}