// FILE: textobject.h
// DATE: 2/27/13
// DESC: implementation of the class to manage an object of text

#include "textobject.h"

TextObject::TextObject()
{
	m_vertexBuffer = NULL;
	m_indexBuffer = NULL;
	m_text = "";
	m_positionX = 0.0f;
	m_positionY = 0.0f;
	m_recreate = true;
	m_red = 1.0f;
	m_green = 1.0f;
	m_blue = 1.0f;
}
TextObject::TextObject(const TextObject& textobject)
{
	m_vertexBuffer = NULL;
	m_indexBuffer = NULL;
	m_text = "";
	m_positionX = 0.0f;
	m_positionY = 0.0f;
	m_recreate = true;
	m_red = 1.0f;
	m_green = 1.0f;
	m_blue = 1.0f;
}
TextObject::~TextObject()
{

}

bool TextObject::Initialize(GraphicsObject* graphics, std::string text, float positionX, float positionY)
{
	VertexType* vertices;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc;
	D3D11_BUFFER_DESC indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData;
	D3D11_SUBRESOURCE_DATA indexData;
	HRESULT result;

	m_text = text;
	m_positionX = positionX;
	m_positionY = positionY;

	m_vertexCount = 6 * text.length();
	m_indexCount = 6 * text.length();

	vertices = new VertexType[m_vertexCount];
	if (!vertices)
		// throw std::exception("Error Initializing Vertex Array in TextObject");
		return false;

	indices = new unsigned long[m_indexCount];
	if (!indices)
		// throw std::exception("Error Initializing Index Array in TextObject");
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

	result = graphics->GetD3D()->GetDevice()->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if (FAILED(result))
		// throw std::exception("Error Initializing Vertex Buffer in TextObject");
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

	result = graphics->GetD3D()->GetDevice()->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if (FAILED(result))
		// throw std::exception("Error Initializing Index Buffer in TextObject");
		return false;

	delete [] vertices;
	vertices = NULL;

	delete [] indices;
	indices = NULL;

	return true;
}
void TextObject::Shutdown()
{
	if (m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = NULL;
	}
	if (m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = NULL;
	}
}

void TextObject::Recreate(GraphicsObject* graphics, FontObject* font)
{
	if (!m_recreate)
		return;

	float drawX, drawY;
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	VertexType* vertices;
	VertexType* verticesPtr;
	unsigned int* indices;
	unsigned int* indicesPtr;

	drawX = (float)(((graphics->GetScreenWidth() / 2) * -1) + m_positionX);
	drawY = (float)((graphics->GetScreenHeight() / 2) - m_positionY);

	m_vertexCount = 6 * m_text.length();
	m_indexCount = 6 * m_text.length();

	// create new vertices
	vertices = new VertexType[m_vertexCount];
	if (!vertices)
		throw std::exception("Error recreating text object vertices");

	memset(vertices, 0, sizeof(VertexType) * m_vertexCount);
	font->BuildVertexArray((void*)vertices, m_text.c_str(), drawX, drawY);

	result = graphics->GetD3D()->GetDeviceContext()->Map(m_vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result))
		throw std::exception("Error recreating text object vertex mapping");

	verticesPtr = (VertexType*)mappedResource.pData;
	memcpy(verticesPtr, (void*)vertices, sizeof(VertexType) * m_vertexCount);
	graphics->GetD3D()->GetDeviceContext()->Unmap(m_vertexBuffer, 0);

	delete [] vertices;
	vertices = NULL;

	m_recreate = false;
	return;

	// create new indices
	indices = new unsigned int[m_indexCount];
	if (!indices)
		throw std::exception("Error recreating text object indices");

	for (unsigned int i = 1; i < (unsigned int)m_indexCount; i++)
		indices[i] = i;

	result = graphics->GetD3D()->GetDeviceContext()->Map(m_indexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result))
		throw std::exception("Error recreating text object indices mapping");

	indicesPtr = (unsigned int*)mappedResource.pData;
	memcpy(indicesPtr, (void*)indices, sizeof(unsigned int) * m_indexCount);
	graphics->GetD3D()->GetDeviceContext()->Unmap(m_indexBuffer, 0);

	delete [] indices;
	indices = NULL;

}

void TextObject::SetText(std::string text)
{
	if (m_text == text)
		return;

	m_text = text;
	m_recreate = true;
}
void TextObject::SetPosition(float positionX, float positionY)
{
	if (m_positionX == positionX && m_positionY == positionY)
		return;

	m_positionX = positionX;
	m_positionY = positionY;
	m_recreate = true;
}