// FILE: BitmapObject.cpp
// DATE: 2/24/13
// DESC: implementation of a class to manage a 2D image

#include "BitmapObject.h"

BitmapObject::BitmapObject()
{
	m_vertexBuffer = NULL;
	m_indexBuffer = NULL;
	m_texture = NULL;

	m_scaleX = 1.0f;
	m_scaleY = 1.0f;
	m_rotation = 0.0f;
}
BitmapObject::BitmapObject(const BitmapObject&)
{
	m_vertexBuffer = NULL;
	m_indexBuffer = NULL;
	m_texture = NULL;
	
	m_scaleX = 1.0f;
	m_scaleY = 1.0f;
	m_rotation = 0.0f;
}
BitmapObject::~BitmapObject()
{

}

bool BitmapObject::Initialize(GraphicsObject* graphics, WCHAR* textureFilename, int bitmapWidth, int bitmapHeight)
{
	m_screenWidth = graphics->GetScreenWidth();
	m_screenHeight = graphics->GetScreenHeight();

	m_bitmapWidth = bitmapWidth;
	m_bitmapHeight = bitmapHeight;

	m_positionX = -1;
	m_positionY = -1;

	if (!InitializeBuffers(graphics->GetD3D()->GetDevice()))
		return false;

	if (!LoadTexture(graphics->GetD3D()->GetDevice(), textureFilename))
		return false;

	return true;
}
void BitmapObject::Shutdown()
{
	ReleaseTexture();
	ShutdownBuffers();
}
bool BitmapObject::Render(GraphicsObject* graphics)
{
	if (!UpdateBuffers(graphics->GetD3D()->GetDeviceContext()))
		return false;

	RenderBuffers(graphics);

	return true;
}

void BitmapObject::SetPosition(int positionX, int positionY)
{
	m_positionX = positionX;
	m_positionY = positionY;
}
void BitmapObject::SetScale(float scale)
{
	m_scaleX = scale;
	m_scaleY = scale;
}
void BitmapObject::SetScale(float scaleX, float scaleY)
{
	m_scaleX = scaleX;
	m_scaleY = scaleY;
}
void BitmapObject::SetRotation(float rotation)
{
	m_rotation = rotation;
}

int BitmapObject::GetIndexCount()
{
	return m_indexCount;
}
ID3D11ShaderResourceView* BitmapObject::GetTexture()
{
	return m_texture->GetTexture();
}

bool BitmapObject::InitializeBuffers(ID3D11Device* device)
{
	VertexType* vertices;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;

	m_vertexCount = 6;
	m_indexCount = 6;

	vertices = new VertexType[m_vertexCount];
	if (!vertices)
		return false;

	indices = new unsigned long[m_indexCount];
	if (!indices)
		return false;

	memset(vertices, 0, sizeof(VertexType)*m_vertexCount);

	for (int i = 0; i < m_indexCount; i++)
		indices[i] = i;

	vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if (FAILED(result))
		return false;

	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if(FAILED(result))
		return false;

	delete [] vertices;
	vertices = NULL;

	delete [] indices;
	indices = NULL;

	return true;
}
void BitmapObject::ShutdownBuffers()
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
bool BitmapObject::UpdateBuffers(ID3D11DeviceContext* deviceContext)
{
	float left, right, top, bottom;
	VertexType* vertices;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	VertexType* verticesPtr;
	HRESULT result;

	left = (float)m_positionX;
	right = left + (float)m_bitmapWidth * m_scaleX;
	top = (float)m_positionY;
	bottom = top - (float)m_bitmapHeight * m_scaleY;

	vertices = new VertexType[m_vertexCount];
	if (!vertices)
		return false;

	vertices[0].position = D3DXVECTOR3(left, top, 0.0f);
	vertices[0].texture = D3DXVECTOR2(0.0f, 0.0f);

	vertices[1].position = D3DXVECTOR3(right, bottom, 0.0f);
	vertices[1].texture = D3DXVECTOR2(1.0f, 1.0f);

	vertices[2].position = D3DXVECTOR3(left, bottom, 0.0f);
	vertices[2].texture = D3DXVECTOR2(0.0f, 1.0f);

	vertices[3].position = D3DXVECTOR3(left, top, 0.0f);
	vertices[3].texture = D3DXVECTOR2(0.0f, 0.0f);

	vertices[4].position = D3DXVECTOR3(right, top, 0.0f);
	vertices[4].texture = D3DXVECTOR2(1.0f, 0.0f);

	vertices[5].position = D3DXVECTOR3(right, bottom, 0.0f);
	vertices[5].texture = D3DXVECTOR2(1.0f, 1.0f);

	result = deviceContext->Map(m_vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result))
		return false;

	verticesPtr = (VertexType*)mappedResource.pData;
	memcpy(verticesPtr, (void*)vertices, sizeof(VertexType)*m_vertexCount);
	deviceContext->Unmap(m_vertexBuffer, 0);

	delete [] vertices;
	vertices = NULL;

	return true;
}
void BitmapObject::RenderBuffers(GraphicsObject* graphics)
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
		m_indexCount, 
		worldMatrix,
		viewMatrix,
		orthoMatrix,
		m_texture->GetTexture());
}

bool BitmapObject::LoadTexture(ID3D11Device* device, WCHAR* filename)
{
	m_texture = new TextureClass;
	if (!m_texture)
		return false;

	if (!(m_texture->Initialize(device, filename)))
		return false;

	return true;
}
void BitmapObject::ReleaseTexture()
{
	if (m_texture)
	{
		m_texture->Shutdown();
		delete m_texture;
		m_texture = NULL;
	}
}