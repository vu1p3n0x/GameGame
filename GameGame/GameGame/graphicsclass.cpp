// FILE: graphicsclass.cpp
// DATE: 2/22/13
// DESC: implemenation for the graphics class to manage window

#include "graphicsclass.h"

GraphicsClass::GraphicsClass()
{
	m_d3d = NULL;
}
GraphicsClass::GraphicsClass(const GraphicsClass& graphicsclass)
{
	m_d3d = NULL;
}
GraphicsClass::~GraphicsClass()
{

}

bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	m_d3d = new D3DClass;
	if (!m_d3d)
		return false;

	if (!(m_d3d->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_FAR, SCREEN_NEAR)))
	{
		MessageBox(hwnd, L"Could not initialize Direct3D", L"Error", MB_OK);
		return false;
	}

	return true;
}
void GraphicsClass::Shutdown()
{
	if (m_d3d)
	{
		m_d3d->Shutdown();
		delete m_d3d;
		m_d3d = NULL;
	}
}

bool GraphicsClass::Frame()
{
	if (!Render())
		return false;

	return true;
}
bool GraphicsClass::Render()
{
	m_d3d->BeginScene(0.5f, 0.5f, 0.5f, 1.0f);

	m_d3d->EndScene();
	return true;
}