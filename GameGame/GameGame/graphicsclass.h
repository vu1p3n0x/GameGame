// FILE: graphicsclass.h
// DATE: 2/22/13
// DESC: declaration for the graphics class to manage window

#ifndef GRAPHICSCLASS_H
#define GRAPHICSCLASS_H

#include <Windows.h>
#include "d3dclass.h"

const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
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

	bool Render();
};

#endif