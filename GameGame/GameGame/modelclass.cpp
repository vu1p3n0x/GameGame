// FILE: modelclass.cpp
// DATE: 2/22/13
// DESC: implementation of the model class to manage displaying on models

#include "modelclass.h"

ModelClass::ModelClass()
{
	m_vertexBuffer = NULL;
	m_indexBuffer = NULL;
	m_texture = NULL;
}
ModelClass::ModelClass(const ModelClass& modelclass)
{
	m_vertexBuffer = NULL;
	m_indexBuffer = NULL;
	m_texture = NULL;
}
ModelClass::~ModelClass()
{

}

bool ModelClass::Initialize(ID3D11Device* device, WCHAR* textureFilename)
{
	if (!InitializeBuffers(device))
		return false;

	if (!LoadTexture(device, textureFilename))
		return false;

	return true;
}
void ModelClass::Shutdown()
{
	ReleaseTexture();
	ShutdownBuffers();
}
void ModelClass::Render(ID3D11DeviceContext* deviceContext)
{
	RenderBuffers(deviceContext);
}

int ModelClass::GetIndexCount()
{
	return m_indexCount;
}
ID3D11ShaderResourceView* ModelClass::GetTexture()
{
	return m_texture->GetTexture();
}

bool ModelClass::InitializeBuffers(ID3D11Device* device)
{
	VertexType* vertices;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;

	m_vertexCount = 4;
	m_indexCount = 6;

	vertices = new VertexType[m_vertexCount];
	if (!vertices)
		return false;

	indices = new unsigned long[m_indexCount];
	if (!indices)
		return false;

	vertices[0].position = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
	vertices[0].texture = D3DXVECTOR2(0.0f, 1.0f);

	vertices[1].position = D3DXVECTOR3(-1.0f, 1.0f, 0.0f);
	vertices[1].texture = D3DXVECTOR2(0.0f, 0.0f);
	
	vertices[2].position = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
	vertices[2].texture = D3DXVECTOR2(1.0f, 0.0f);

	vertices[3].position = D3DXVECTOR3(1.0f, -1.0f, 0.0f);
	vertices[3].texture = D3DXVECTOR2(1.0f, 1.0f);
	
	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 0;
	indices[4] = 2;
	indices[5] = 3;
	
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
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
void ModelClass::ShutdownBuffers()
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
void ModelClass::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	unsigned int stride;
	unsigned int offset;

	stride = sizeof(VertexType);
	offset = 0;

	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);
	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

bool ModelClass::LoadTexture(ID3D11Device* device, WCHAR* filename)
{
	m_texture = new TextureClass;
	if (!m_texture)
		return false;

	if (!(m_texture->Initialize(device, filename)))
		return false;

	return true;
}
void ModelClass::ReleaseTexture()
{
	if (m_texture)
	{
		m_texture->Shutdown();
		delete m_texture;
		m_texture = NULL;
	}
}