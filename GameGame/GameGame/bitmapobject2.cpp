// FILE: BitmapObject2.cpp
// DATE: 2/24/13
// DESC: implementation of a class to manage a 2D image

#include "BitmapObject2.h"

BitmapObject2::BitmapObject2()
{
	m_vertexBuffer = NULL;
	m_indexBuffer = NULL;
	m_texture = NULL;
}
BitmapObject2::BitmapObject2(const BitmapObject2&)
{
	m_vertexBuffer = NULL;
	m_indexBuffer = NULL;
	m_texture = NULL;
}
BitmapObject2::~BitmapObject2()
{

}

/// <summary>
/// Initializes the BitmapObject with the texture from file specified
/// </summary>
bool BitmapObject2::Initialize(GraphicsObject* graphics, WCHAR* textureFilename, int bitmapWidth, int bitmapHeight)
{
	m_screenWidth = graphics->GetScreenWidth();
	m_screenHeight = graphics->GetScreenHeight();

	m_bitmapWidth = bitmapWidth;
	m_bitmapHeight = bitmapHeight;

	if (!InitializeBuffers(graphics->GetD3D()->GetDevice()))
		return false;

	if (!LoadTexture(graphics->GetD3D()->GetDevice(), textureFilename))
		return false;

	SetPosition(0.0f, 0.0f);
	SetRotation(0.0f);
	SetScale(1.0f);
	SetOrigin(0.0f, 0.0f);

	return true;
}
void BitmapObject2::Shutdown()
{
	ReleaseTexture();
	ShutdownBuffers();
}
bool BitmapObject2::Render(GraphicsObject* graphics)
{
	graphics->GetD3D()->TurnOnAlphaBlending();
	RenderBuffers(graphics);
	graphics->GetD3D()->TurnOffAlphaBlending();

	return true;
}

void BitmapObject2::SetPosition(float positionX, float positionY)
{
	D3DXMatrixTranslation(&m_position, positionX - m_screenWidth/2, positionY - m_screenHeight/2, 0.0f);
}
void BitmapObject2::SetScale(float scale)
{
	D3DXMatrixScaling(&m_scale, scale * m_bitmapWidth, scale * m_bitmapHeight, 1.0f);
}
void BitmapObject2::SetScale(float scaleX, float scaleY)
{
	D3DXMatrixScaling(&m_scale, scaleX * m_bitmapWidth, scaleY * m_bitmapHeight, 1.0f);
}
void BitmapObject2::SetRotation(float rotation)
{
	D3DXMatrixRotationZ(&m_rotation, rotation);
}
void BitmapObject2::SetOrigin(float offsetX, float offsetY)
{
	D3DXMatrixTranslation(&m_origin, -1*offsetX, -1*offsetY, 0.0f);
}

bool BitmapObject2::InitializeBuffers(ID3D11Device* device)
{
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;

	// vertex initialization // 
	VertexType* vertices;
	vertices = new VertexType[VERTEXCOUNT];
	if (!vertices)
		return false;

	vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * VERTEXCOUNT;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	vertices[0].position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertices[0].texture = D3DXVECTOR2(0.0f, 1.0f);

	vertices[1].position = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertices[1].texture = D3DXVECTOR2(0.0f, 0.0f);

	vertices[2].position = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
	vertices[2].texture = D3DXVECTOR2(1.0f, 0.0f);

	vertices[3].position = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	vertices[3].texture = D3DXVECTOR2(1.0f, 1.0f);

	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if (FAILED(result))
		return false;
	delete [] vertices;
	vertices = NULL;

	// index initialization //
	unsigned long* indices;
	indices = new unsigned long[INDEXCOUNT];
	if (!indices)
		return false;

	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * INDEXCOUNT;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;
	
	indices[0] = 1;
	indices[1] = 3;
	indices[2] = 0;
	indices[3] = 1;
	indices[4] = 2;
	indices[5] = 3;

	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if(FAILED(result))
		return false;
	delete [] indices;
	indices = NULL;

	return true;
}
void BitmapObject2::ShutdownBuffers()
{
	if (m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = NULL;
	}

	if (m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = NULL;
	}
}
void BitmapObject2::RenderBuffers(GraphicsObject* graphics)
{
	unsigned int stride;
	unsigned int offset;
	D3DXMATRIX worldMatrix, viewMatrix, orthoMatrix;

	stride = sizeof(VertexType);
	offset = 0;

	graphics->GetD3D()->GetDeviceContext()->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);
	graphics->GetD3D()->GetDeviceContext()->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	graphics->GetD3D()->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	graphics->GetD3D()->GetWorldMatrix(worldMatrix);
	graphics->GetCamera()->GetViewMatrix(viewMatrix);
	graphics->GetD3D()->GetOrthoMatrix(orthoMatrix);

	graphics->GetTextureShader()->Render(
		graphics->GetD3D()->GetDeviceContext(),
		INDEXCOUNT, 
		m_origin * m_scale * m_rotation * m_position * worldMatrix,
		viewMatrix,
		orthoMatrix,
		m_texture->GetTexture());
}

bool BitmapObject2::LoadTexture(ID3D11Device* device, WCHAR* filename)
{
	m_texture = new TextureClass;
	if (!m_texture)
		return false;

	if (!(m_texture->Initialize(device, filename)))
		return false;

	return true;
}
void BitmapObject2::ReleaseTexture()
{
	if (m_texture)
	{
		m_texture->Shutdown();
		delete m_texture;
		m_texture = NULL;
	}
}