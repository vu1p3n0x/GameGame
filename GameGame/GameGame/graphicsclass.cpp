// FILE: graphicsclass.cpp
// DATE: 2/22/13
// DESC: implemenation for the graphics class to manage window

#include "graphicsclass.h"

GraphicsClass::GraphicsClass()
{
	m_d3d = NULL;
	m_camera = NULL;
	m_model = NULL;
	m_colorShader = NULL;
}
GraphicsClass::GraphicsClass(const GraphicsClass& graphicsclass)
{
	m_d3d = NULL;
	m_camera = NULL;
	m_model = NULL;
	m_colorShader = NULL;
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

	m_camera->SetPosition(0.0f, 0.0f, -10.0f);

	m_model = new ModelClass;
	if (!m_model)
		return false;

	if (!(m_model->Initialize(m_d3d->GetDevice(), L"")))
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	m_colorShader = new ColorShaderClass;
	if (!m_colorShader)
		return false;

	if (!(m_colorShader->Initialize(m_d3d->GetDevice(), hwnd)))
		return false;

	return true;
}
void GraphicsClass::Shutdown()
{
	if (m_colorShader)
	{
		m_colorShader->Shutdown();
		delete m_colorShader;
		m_colorShader = NULL;
	}

	if (m_model)
	{
		m_model->Shutdown();
		delete m_model;
		m_model = NULL;
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
	D3DXMATRIX viewMatrix, projectionMatrix, worldMatrix;

	m_d3d->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	m_camera->Render();

	m_camera->GetViewMatrix(viewMatrix);
	m_d3d->GetWorldMatrix(worldMatrix);
	m_d3d->GetProjectionMatrix(projectionMatrix);

	m_model->Render(m_d3d->GetDeviceContext());

	if (!(m_colorShader->Render(m_d3d->GetDeviceContext(), m_model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix)))
		return false;

	m_d3d->EndScene();
	return true;
}