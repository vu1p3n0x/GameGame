// FILE: graphicsobject.cpp
// DATE: 2/26/13
// DESC: imlementation of the graphics class to manage the display

#include "graphicsobject.h"
#include "applicationobject.h"

GraphicsObject::GraphicsObject(HWND hwnd, int width, int height, bool fullscreen)
{
	m_screenWidth = width;
	m_screenHeight = height;

	m_d3d = new D3DClass;
	if (!m_d3d)
		throw std::exception("Error Creating the Direct3D Object");
	if (!(m_d3d->Initialize(width, height, true, hwnd, fullscreen, 1000.0f, 0.1f)))
		throw std::exception("Error Initializing the Direct3D Object");

	m_camera = new CameraClass;
	if (!m_camera)
		throw std::exception("Error Creating the Camera");
	m_camera->SetPosition(0.0f, 0.0f, -1.0f);

	m_textureShader = new TextureShaderClass;
	if (!m_textureShader)
		throw std::exception("Error Creating the Texture Shader");
	if (!(m_textureShader->Initialize(m_d3d->GetDevice(), hwnd)))
		throw std::exception("Error Initializing the Texture Shader");

	m_fontShader = new FontShaderClass;
	if (!m_fontShader)
		throw std::exception("Error Creating the Font Shader");
	if (!(m_fontShader->Initialize(m_d3d->GetDevice(), hwnd)))
		throw std::exception("Error Initializing the Font Shader");
}
GraphicsObject::GraphicsObject(const GraphicsObject& graphicsobject)
{

}
GraphicsObject::~GraphicsObject()
{
	if (m_fontShader)
	{
		m_fontShader->Shutdown();
		delete m_fontShader;
		m_fontShader = NULL;
	}

	if (m_textureShader)
	{
		m_textureShader->Shutdown();
		delete m_textureShader;
		m_textureShader = NULL;
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

D3DClass* GraphicsObject::GetD3D()
{
	return m_d3d;
}
CameraClass* GraphicsObject::GetCamera()
{
	return m_camera;
}
TextureShaderClass* GraphicsObject::GetTextureShader()
{
	return m_textureShader;
}
FontShaderClass* GraphicsObject::GetFontShader()
{
	return m_fontShader;
}
int GraphicsObject::GetScreenWidth()
{
	return m_screenWidth;
}
int GraphicsObject::GetScreenHeight()
{
	return m_screenHeight;
}