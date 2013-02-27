// FILE: graphicsclass.h
// DATE: 2/22/13 - 2/24/13
// DESC: declaration for the graphics class to manage window

#ifndef GRAPHICSCLASS_H
#define GRAPHICSCLASS_H

#include <Windows.h>
#include "d3dclass.h"
#include "cameraclass.h"
#include "bitmapclass.h"
#include "textureshaderclass.h"
#include "textclass.h"

const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = false;
const float SCREEN_FAR = 1000.0f;
const float SCREEN_NEAR = 0.1f;

class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(int, int, HWND);
	void Shutdown();

	bool Frame();

private:
	D3DClass* m_d3d;
	CameraClass* m_camera;
	BitmapClass* m_bitmap;
	TextureShaderClass* m_textureShader;
	TextClass* m_text;      

	bool Render();
};

#endif