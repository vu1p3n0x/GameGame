// FILE: BitmapObject2.h
// DATE: 3/5/13
// DESC: declaration of a class to manage a 2D image

#ifndef BITMAPOBJECT2_H
#define BITMAPOBJECT2_H

#include <d3d11.h>
#include <d3dx10math.h>
#include "textureclass.h"
#include "graphicsobject.h"

class BitmapObject2
{
public:
	BitmapObject2();
	BitmapObject2(const BitmapObject2&);
	~BitmapObject2();
	
	bool Initialize(GraphicsObject* graphics, WCHAR* textureFilename, int bitmapWidth, int bitmapHeight);
	bool Render(GraphicsObject* graphics);
	void Shutdown();

	void SetPosition(float positionX, float positionY);
	void SetScale(float scale);
	void SetScale(float scaleX, float scaleY);
	void SetRotation(float rotation);
	void SetOrigin(float offsetX, float offsetY);

private:
	struct VertexType
	{
		D3DXVECTOR3 position;
		D3DXVECTOR2 texture;
	};

	bool InitializeBuffers(ID3D11Device* device);
	void ShutdownBuffers();
	void RenderBuffers(GraphicsObject* graphics);

	bool LoadTexture(ID3D11Device* device, WCHAR* filename);
	void ReleaseTexture();

	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	int m_vertexCount, m_indexCount;
	TextureClass* m_texture;

	int m_screenWidth, m_screenHeight;
	int m_bitmapWidth, m_bitmapHeight;

	D3DXMATRIX m_position;
	D3DXMATRIX m_rotation;
	D3DXMATRIX m_scale;
	D3DXMATRIX m_origin;

	static const unsigned short VERTEXCOUNT = 4;
	static const unsigned short INDEXCOUNT = 6;
};

#endif