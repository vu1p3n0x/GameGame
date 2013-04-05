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
void Wilt::Font::BuildArrays(void* vertices, unsigned int* indices, const char* text)
{
	VertexType* vertexPtr;
	int letter, length;
	float offset, split;

	length = (int)strlen(text);
	offset = 0.0f;

	vertexPtr = (VertexType*)vertices;

	for (int i = 0; i < length; i++)
	{
		letter = (int)text[i]-32;

		if (letter == 0)
			split = 0.08f;
		else
			split = m_fontData[letter+1] - m_fontData[letter];

		indices[i*6+0] = i*6+1;
		indices[i*6+1] = i*6+3;
		indices[i*6+2] = i*6+0;
		indices[i*6+3] = i*6+1;
		indices[i*6+4] = i*6+2;
		indices[i*6+5] = i*6+3;

		// bottom left
		vertexPtr[i*4+0].position = D3DXVECTOR3(offset, 0.0f, 0.0f);
		vertexPtr[i*4+0].texture = D3DXVECTOR2(m_fontData[letter], 1.0f);

		// top left
		vertexPtr[i*4+1].position = D3DXVECTOR3(offset, 1.0f, 0.0f);
		vertexPtr[i*4+1].texture = D3DXVECTOR2(m_fontData[letter], 0.0f);

		// top right
		vertexPtr[i*4+2].position = D3DXVECTOR3(offset + split, 1.0f, 0.0f);
		vertexPtr[i*4+2].texture = D3DXVECTOR2(m_fontData[letter+1], 0.0f);

		// bottom right
		vertexPtr[i*4+3].position = D3DXVECTOR3(offset + split, 0.0f, 0.0f);
		vertexPtr[i*4+3].texture = D3DXVECTOR2(m_fontData[letter+1], 1.0f);

		offset = offset + split + 0.03f;
	}
}
