// FILE: fontclass.cpp
// DATE: 2/24/13
// DESC: implementation of the class to manage fonts

#include "fontclass.h"

FontClass::FontClass()
{
	m_font = NULL;
	m_texture = NULL;
}
FontClass::FontClass(const FontClass&)
{
	m_font = NULL;
	m_texture = NULL;
}
FontClass::~FontClass()
{

}

bool FontClass::Initialize(ID3D11Device* device, char* fontFilename, WCHAR* textureFilename)
{
	if (!LoadFontData(fontFilename))
		return false;

	if (!LoadTexture(device, textureFilename))
		return false;

	return true;
}
void FontClass::Shutdown()
{
	ReleaseTexture();
	ReleaseFontData();
}

bool FontClass::LoadFontData(char* filename)
{
	std::ifstream fin;
	char temp;

	m_font = new FontType[95];
	if (!m_font)
		return false;

	fin.open(filename);
	if (fin.fail())
		return false;

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

	return true;
}
void FontClass::ReleaseFontData()
{
	if (m_font)
	{
		delete [] m_font;
		m_font = NULL;
	}
}

bool FontClass::LoadTexture(ID3D11Device* device, WCHAR* filename)
{
	m_texture = new TextureClass;
	if (!m_texture)
		return false;

	if (!(m_texture->Initialize(device, filename)))
		return false;

	return true;
}
void FontClass::ReleaseTexture()
{
	if (m_texture)
	{
		m_texture->Shutdown();
		delete m_texture;
		m_texture = NULL;
	}
}

ID3D11ShaderResourceView* FontClass::GetTexture()
{
	return m_texture->GetTexture();
}
void FontClass::BuildVertexArray(void* vertices, const char* sentence, float drawX, float drawY)
{
	VertexType* vertexPtr;
	int numLetters, index, letter;

	vertexPtr = (VertexType*)vertices;

	numLetters = (int)strlen(sentence);
	index = 0;

	for (int i = 0; i < numLetters; i++)
	{
		letter = (int)sentence[i] - 32;

		if (letter == 0)
			drawX = drawX+3.0f;
		else
		{
			vertexPtr[index].position = D3DXVECTOR3(drawX, drawY, 0.0f);
			vertexPtr[index].texture = D3DXVECTOR2(m_font[letter].left, 0.0f);
			index++;

			vertexPtr[index].position = D3DXVECTOR3((drawX + m_font[letter].size), (drawY - 16), 0.0f);
			vertexPtr[index].texture = D3DXVECTOR2(m_font[letter].right, 1.0f);
			index++;

			vertexPtr[index].position = D3DXVECTOR3(drawX, (drawY - 16), 0.0f);
			vertexPtr[index].texture = D3DXVECTOR2(m_font[letter].left, 1.0f);
			index++;

			vertexPtr[index].position = D3DXVECTOR3(drawX, drawY, 0.0f);
			vertexPtr[index].texture = D3DXVECTOR2(m_font[letter].left, 0.0f);
			index++;

			vertexPtr[index].position = D3DXVECTOR3(drawX + m_font[letter].size, drawY, 0.0f);
			vertexPtr[index].texture = D3DXVECTOR2(m_font[letter].right, 0.0f);
			index++;

			vertexPtr[index].position = D3DXVECTOR3((drawX + m_font[letter].size), (drawY - 16), 0.0f);
			vertexPtr[index].texture = D3DXVECTOR2(m_font[letter].right, 1.0f);
			index++;

			drawX = drawX + m_font[letter].size + 1.0f;
		}
	}
}