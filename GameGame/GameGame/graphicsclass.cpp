// FILE: graphicsclass.cpp
// DATE: 2/22/13
// DESC: implemenation for the graphics class to manage window

#include "graphicsclass.h"

GraphicsClass::GraphicsClass()
{
	m_d3d = NULL;
	m_camera = NULL;
	m_bitmap = NULL;
	m_textureShader = NULL;
}
GraphicsClass::GraphicsClass(const GraphicsClass& graphicsclass)
{
	m_d3d = NULL;
	m_camera = NULL;
	m_bitmap = NULL;
	m_textureShader = NULL;
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

	m_camera = new CameraClass;
	if (!m_camera)
		return false;

	m_camera->SetPosition(0.0f, 0.0f, -3.0f);

	m_bitmap = new BitmapClass;
	if (!m_bitmap)
		return false;

	if (!(m_bitmap->Initialize(m_d3d->GetDevice(), screenWidth, screenHeight, L"../GameGame/data/seafloor.dds", 256, 256)))
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	m_textureShader = new TextureShaderClass;
	if (!m_textureShader)
		return false;

	if (!(m_textureShader->Initialize(m_d3d->GetDevice(), hwnd)))
		return false;

	return true;
}
void GraphicsClass::Shutdown()
{
	if (m_textureShader)
	{
		m_textureShader->Shutdown();
		delete m_textureShader;
		m_textureShader = NULL;
	}

	if (m_bitmap)
	{
		m_bitmap->Shutdown();
		delete m_bitmap;
		m_bitmap = NULL;
	}

	if (m_camera)
	{
		delete m_camera;
		m_camera = NULL;
	}

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
	D3DXMATRIX viewMatrix, projectionMatrix, worldMatrix, orthoMatrix;

	m_d3d->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	m_camera->Render();

	m_camera->GetViewMatrix(viewMatrix);
	m_d3d->GetWorldMatrix(worldMatrix);
	m_d3d->GetProjectionMatrix(projectionMatrix);
	m_d3d->GetOrthoMatrix(orthoMatrix);

	m_d3d->TurnZBufferOff();

	if (!(m_bitmap->Render(m_d3d->GetDeviceContext(), 100, 100)))
		return false;

	if (!(m_textureShader->Render(m_d3d->GetDeviceContext(), m_bitmap->GetIndexCount(), worldMatrix, viewMatrix, orthoMatrix, m_bitmap->GetTexture())))
		return false;

	m_d3d->TurnZBufferOn();

	m_d3d->EndScene();
	return true;
}