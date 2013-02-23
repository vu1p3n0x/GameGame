// FILE: textureclass.cpp
// DATE: 2/22/13
// DESC: implementation of the texture class to represent a texture

#include "textureclass.h"

TextureClass::TextureClass()
{
	m_texture = NULL;
}

TextureClass::TextureClass(const TextureClass& textureclass)
{
	m_texture = NULL;
}

TextureClass::~TextureClass()
{

}

bool TextureClass::Initialize(ID3D11Device* device, WCHAR* filename)
{
	HRESULT result;

	result = D3DX11CreateShaderResourceViewFromFile(device, filename, NULL, NULL, &m_texture, NULL);
	if (FAILED(result))
		return false;

	return true;
}

void TextureClass::Shutdown()
{
	if (m_texture)
	{
		m_texture->Release();
		delete m_texture;
		m_texture = NULL;
	}
}

ID3D11ShaderResourceView* TextureClass::GetTexture()
{
	return m_texture;
}