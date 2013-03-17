// FILE: fontobject.cpp
// DATE: 2/27/13
// DESC: implementation of the object to manage a font

#include "fontobject.h"

FontObject::FontObject()
{
	m_font = NULL;
	m_texture = NULL;
}
FontObject::FontObject(const FontObject& fontobject)
{
	m_font = NULL;
	m_texture = NULL;
}
FontObject::~FontObject()
{

}

bool FontObject::Initialize(ID3D11Device* device, char* fontFilename, WCHAR* textureFilename)
{
	// load font data
	std::ifstream fin;
	char temp;

	m_font = new FontType[95];
	if (!m_font)
		throw std::exception("Error creating font type");

	fin.open(fontFilename);
	if (fin.fail())
		throw std::exception("Error: could not open font data file");

	for (int i = 0; i < 95; i++)
	{
		fin.get(temp);
		while(temp != ' ')
			fin.get(temp);

		fin.get(temp);
		while(temp != ' ')
			fin.get(temp);

		fin >> m_font[i].left;
		fin >> m_font[i].right;
		fin >> m_font[i].size;
	}

	fin.close();
	
	// load font texture
	m_texture = new TextureClass;
	if (!m_texture)
		throw std::exception("Error creating font texture");

	if (!(m_texture->Initialize(device, textureFilename)))
		throw std::exception("Error initializing font texture");

	return true;
}
void FontObject::RenderText(GraphicsObject* graphics, TextObject* textobject)
{
	unsigned int stride, offset;
	D3DXVECTOR4 pixelColor;
	D3DXMATRIX worldMatrix, viewMatrix, orthoMatrix;

	stride = sizeof(VertexType);
	offset = 0;

	textobject->Recreate(graphics, this);

	graphics->GetD3D()->GetDeviceContext()->IASetVertexBuffers(0, 1, &textobject->m_vertexBuffer, &stride, &offset);
	graphics->GetD3D()->GetDeviceContext()->IASetIndexBuffer(textobject->m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	graphics->GetD3D()->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	graphics->GetD3D()->GetWorldMatrix(worldMatrix);
	graphics->GetCamera()->GetViewMatrix(viewMatrix);
	graphics->GetD3D()->GetOrthoMatrix(orthoMatrix);

	pixelColor = D3DXVECTOR4(textobject->m_red, textobject->m_green, textobject->m_blue, 1.0f);

	graphics->GetFontShader()->Render(
		graphics->GetD3D()->GetDeviceContext(), 
		textobject->m_indexCount,
		worldMatrix,
		viewMatrix,
		orthoMatrix,
		m_texture->GetTexture(),
		pixelColor);
}
void FontObject::Shutdown()
{
	if (m_font)
	{
		delete [] m_font;
		m_font = NULL;
	}

	if (m_texture)
	{
		m_texture->Shutdown();
		delete m_texture;
		m_texture = NULL;
	}
}

ID3D11ShaderResourceView* FontObject::GetTexture()
{
	return m_texture->GetTexture();
}
void FontObject::BuildVertexArray(void* vertices, const char* text, float positionX, float positionY)
{
	VertexType* vertexPtr;
	int index, letter;

	vertexPtr = (VertexType*)vertices;

	index = 0;
	for (int i = 0; i < (int)strlen(text); i++)
	{
		letter = (int)text[i]-32;

		if (letter == 0)
			positionX = positionX + 3.0f;
		else
		{
			vertexPtr[index].position = D3DXVECTOR3(positionX, positionY, 0.0f);
			vertexPtr[index].texture = D3DXVECTOR2(m_font[letter].left, 0.0f);
			index++;

			vertexPtr[index].position = D3DXVECTOR3((positionX + m_font[letter].size), (positionY - 16), 0.0f);
			vertexPtr[index].texture = D3DXVECTOR2(m_font[letter].right, 1.0f);
			index++;

			vertexPtr[index].position = D3DXVECTOR3(positionX, (positionY - 16), 0.0f);
			vertexPtr[index].texture = D3DXVECTOR2(m_font[letter].left, 1.0f);
			index++;

			vertexPtr[index].position = D3DXVECTOR3(positionX, positionY, 0.0f);
			vertexPtr[index].texture = D3DXVECTOR2(m_font[letter].left, 0.0f);
			index++;

			vertexPtr[index].position = D3DXVECTOR3(positionX + m_font[letter].size, positionY, 0.0f);
			vertexPtr[index].texture = D3DXVECTOR2(m_font[letter].right, 0.0f);
			index++;

			vertexPtr[index].position = D3DXVECTOR3((positionX + m_font[letter].size), (positionY - 16), 0.0f);
			vertexPtr[index].texture = D3DXVECTOR2(m_font[letter].right, 1.0f);
			index++;

			positionX = positionX + m_font[letter].size + 1.0f;
		}
	}
}