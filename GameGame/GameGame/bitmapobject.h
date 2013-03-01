// FILE: BitmapObject.h
// DATE: 2/24/13
// DESC: declaration of a class to manage a 2D image

#ifndef BITMAPOBJECT_H
#define BITMAPOBJECT_H

#include <d3d11.h>
#include <d3dx10math.h>
#include "textureclass.h"
#include "graphicsobject.h"

class BitmapObject
{
public:
	BitmapObject();
	BitmapObject(const BitmapObject&);
	~BitmapObject();

	bool Initialize(GraphicsObject* graphics, WCHAR* textureFilename, int bitmapWidth, int bitmapHeight);
	bool Render(GraphicsObject* graphics, int positionX, int positionY);
	void Shutdown();

	int GetIndexCount();
	ID3D11ShaderResourceView* GetTexture();

private:
	struct VertexType
	{
		D3DXVECTOR3 position;
		D3DXVECTOR2 texture;
	};

	bool InitializeBuffers(ID3D11Device* device);
	void ShutdownBuffers();
	bool UpdateBuffers(ID3D11DeviceContext* deviceContext, int positionX, int positionY);
	void RenderBuffers(GraphicsObject* graphics);

	bool LoadTexture(ID3D11Device* device, WCHAR* filename);
	void ReleaseTexture();

	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	int m_vertexCount, m_indexCount;
	TextureClass* m_texture;

	int m_screenWidth, m_screenHeight;
	int m_bitmapWidth, m_bitmapHeight;
	int m_prevPosX, m_prevPosY;
};

#endif