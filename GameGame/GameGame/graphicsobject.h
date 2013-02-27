// FILE: graphicsobject.h
// DATE: 2/26/13
// DESC: declaration of the graphics class to manage the display

#ifndef GRAPHICSOBJECT_H
#define GRAPHICSOBJECT_H

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <exception>

#include "d3dclass.h"
#include "cameraclass.h"
#include "textureshaderclass.h"
#include "fontshaderclass.h"

class GraphicsObject
{
private:
	D3DClass* m_d3d;
	CameraClass* m_camera;
	TextureShaderClass* m_textureShader;
	FontShaderClass* m_fontShader;

public:
	GraphicsObject(HWND hwnd, int width, int height, bool fullscreen);
	GraphicsObject(const GraphicsObject& graphicsobject);
	~GraphicsObject();

	D3DClass* GetD3D();
	CameraClass* GetCamera();
	FontShaderClass* GetFontShader();
	TextureShaderClass* GetTextureShader();
};

#endif;