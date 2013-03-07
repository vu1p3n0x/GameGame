// FILE: BitmapObject.cpp
// DATE: 3/6/13
// DESC: implementation of a class to manage a 2D image

#include "bitmapobject.h"

BitmapObject::BitmapObject()
{
	m_vertexBuffer = NULL;
	m_indexBuffer = NULL;
	m_texture = NULL;
}
BitmapObject::BitmapObject(const BitmapObject&)
{
	m_vertexBuffer = NULL;
	m_indexBuffer = NULL;
	m_texture = NULL;
}
BitmapObject::~BitmapObject()
{

}

void BitmapObject::Initialize(GraphicsObject* graphics, WCHAR* textureFilename, unsigned int bitmapWidth, unsigned int bitmapHeight)
{
	// get information from graphics card
	if (graphics == NULL)
		throw std::exception("Null pointer exception when initializing bitmap object: GraphicsObject");
	m_screenWidth = graphics->GetScreenWidth();
	m_screenHeight = graphics->GetScreenHeight();

	// get bitmap width
	if (bitmapWidth == 0)
		throw std::exception("bitmap width must be greater than 0");
	m_bitmapWidth = bitmapWidth;

	// get bitmap height
	if (bitmapHeight == 0)
		throw std::exception("bitmap height must be greater than 0");
	m_bitmapHeight = bitmapHeight;

	// create buffers for bitmap object
	InitializeBuffers(graphics->GetD3D()->GetDevice());

	// load texture into graphics memory
	LoadTexture(graphics->GetD3D()->GetDevice(), textureFilename);

	// set default transformations
	SetPosition(0.0f, 0.0f);
	SetRotation(0.0f);
	SetScale(1.0f);
	SetOrigin(0.0f, 0.0f);
}
void BitmapObject::Shutdown()
{
	ReleaseTexture();
	ShutdownBuffers();
}
void BitmapObject::Render(GraphicsObject* graphics)
{
	RenderBuffers(graphics);
}

void BitmapObject::SetPosition(float positionX, float positionY)
{
	D3DXMatrixTranslation(&m_position, positionX - m_screenWidth/2, positionY - m_screenHeight/2, 0.0f);
}
void BitmapObject::SetScale(float scale)
{
	if (scale < 0.0f)
		throw std::range_error("Scale value must be positive");

	D3DXMatrixScaling(&m_scale, scale * m_bitmapWidth, scale * m_bitmapHeight, 1.0f);
}
void BitmapObject::SetScale(float scaleX, float scaleY)
{
	if (scaleX < 0.0f || scaleY < 0.0f)
		throw std::range_error("Scale value must be positive");

	D3DXMatrixScaling(&m_scale, scaleX * m_bitmapWidth, scaleY * m_bitmapHeight, 1.0f);
}
void BitmapObject::SetRotation(float rotation)
{
	D3DXMatrixRotationZ(&m_rotation, rotation);
}
void BitmapObject::SetOrigin(float offsetX, float offsetY)
{
	D3DXMatrixTranslation(&m_origin, -1*offsetX, -1*offsetY, 0.0f);
}

void BitmapObject::InitializeBuffers(ID3D11Device* device)
{
	HRESULT result;

	// vertex initialization // 
	VertexType* vertices;
	vertices = new VertexType[VERTEXCOUNT];
	if (!vertices)
		throw std::exception("Could not create vertex array for BitmapObject");

	D3D11_BUFFER_DESC vertexBufferDesc;
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

	D3D11_SUBRESOURCE_DATA vertexData;
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if (FAILED(result))
		throw std::exception("Could not create vertex buffer for BitmapObject");
	delete [] vertices;
	vertices = NULL;

	// index initialization //
	unsigned long* indices;
	indices = new unsigned long[INDEXCOUNT];
	if (!indices)
		throw std::exception("Could not create index array for BitmapObject");
	
	D3D11_BUFFER_DESC indexBufferDesc;
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
	
	D3D11_SUBRESOURCE_DATA indexData;
	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if(FAILED(result))
		throw std::exception("Could not create index buffer for BitmapObject");
	delete [] indices;
	indices = NULL;
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
		INDEXCOUNT, 
		m_origin * m_scale * m_rotation * m_position * worldMatrix,
		viewMatrix,
		orthoMatrix,
		m_texture->GetTexture());
}

void BitmapObject::LoadTexture(ID3D11Device* device, WCHAR* filename)
{
	m_texture = new TextureClass;
	if (!m_texture)
		throw std::exception("Could not create texture");

	if (!(m_texture->Initialize(device, filename)))
		throw std::exception("Could not initialize texture");
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