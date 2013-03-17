// FILE: mainscreen.h
// DATE: 3/16/13
// DESC: declaration of main screen 

#include "mainscreen.h"
#include "GameScreen.h"

MainScreen::MainScreen()
{
	m_text = new TextObject;
	m_font = new FontObject;
}
MainScreen::MainScreen(const MainScreen& mainscreen)
{
	m_text = new TextObject;
	m_font = new FontObject;
}
MainScreen::~MainScreen()
{
	if (m_text)
	{
		m_text->Shutdown();
		delete m_text;
		m_text = NULL;
	}
	if (m_font)
	{
		m_font->Shutdown();
		delete m_font;
		m_font = NULL;
	}
}

void MainScreen::Initialize(ScreenManagerObject* manager, GraphicsObject* graphics)
{
	ScreenObject::Initialize(manager, graphics);

	if (!m_font->Initialize(graphics->GetD3D()->GetDevice(), "data/fontdata.txt", L"data/font.dds"))
		throw std::exception("Could not Initialize font");
	m_text->Initialize(graphics, "Main Menu", 10, 10);
	
}
void MainScreen::Update(InputObject* input, GraphicsObject* graphics)
{
	if (input->IsButtonTriggered(0))
	{
		GameScreen* screen = new GameScreen;
		screen->Initialize(m_manager, graphics);
		m_manager->SetNextScreen(screen);
	}
}
void MainScreen::Draw(GraphicsObject* graphics)
{
	m_font->RenderText(graphics, m_text);
}
void MainScreen::Shutdown()
{
	ScreenObject::Shutdown();

	if (m_text)
	{
		m_text->Shutdown();
		delete m_text;
		m_text = NULL;
	}
	if (m_font)
	{
		m_font->Shutdown();
		delete m_font;
		m_font = NULL;
	}
}