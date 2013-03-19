// FILE: Font.cpp
// DATE: 2/27/13 - 3/18/13
// DESC: implementation of the object to manage a font

#include "Font.h"

Wilt::Font::Font()
{
	m_texture = NULL;
	m_fontData = NULL;
}
Wilt::Font::~Font()
{
	Shutdown();
}

void Wilt::Font::Initialize(ID3D11Device* device, char* fontFilename, WCHAR* textureFilename)
{
	// load font data
	std::ifstream fin;
	char temp;
	std::string temp2;

	m_fontData = new float[96];
	if (!m_fontData)
		throw std::exception("Error creating font type");

	m_fontData[0] = 0.0f;

	fin.open(fontFilename);
	if (fin.fail())
		throw std::exception("Error: could not open font data file");

	for (int i = 1; i < 96; i++)
	{
		fin.get(temp);
		while(temp != ' ')
			fin.get(temp);

		fin.get(temp);
		while(temp != ' ')
			fin.get(temp);

		fin >> temp2;
		fin >> m_fontData[i];
		fin >> temp2;
	}

	fin.close();
	
	// load font texture
	m_texture = new Texture;
	if (!m_texture)
		throw std::exception("Error creating font texture");

	m_texture->Initialize(device, textureFilename);
}
void Wilt::Font::RenderText(GraphicsObject* graphics, Wilt::Text* textobject)
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
void Wilt::Font::Shutdown()
{
	if (m_fontData)
	{
		delete [] m_fontData;
		m_fontData = NULL;
	}

	if (m_texture)
	{
		m_texture->Shutdown();
		delete m_texture;
		m_texture = NULL;
	}
}

ID3D11ShaderResourceView* Wilt::Font::GetTexture()
{
	return m_texture->GetTexture();
}
void Wilt::Font::BuildVertexArray(void* vertices, const char* text, float positionX, float positionY)
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
