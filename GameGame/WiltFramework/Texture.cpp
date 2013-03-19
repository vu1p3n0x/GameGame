// FILE: Texture.cpp
// DATE: 2/22/13 - 3/18/13
// DESC: implementation of the texture class to represent a texture

#include "Texture.h"

// Constructors and Destructors
Wilt::Texture::Texture()
{
	m_texture = NULL;
	
	m_height = 0;
	m_width = 0;
}
Wilt::Texture::~Texture()
{
	Shutdown();
}

// Basic public functions
void Wilt::Texture::Initialize(ID3D11Device* device, WCHAR* filename)
{
	HRESULT result;
	D3DX11_IMAGE_INFO info;

	result = D3DX11CreateShaderResourceViewFromFileW(device, filename, NULL, NULL, &m_texture, NULL);
	if (FAILED(result))
		throw std::exception("Error: could not create texture");

	result = D3DX11GetImageInfoFromFile(filename, NULL, &info, NULL);
	if (FAILED(result))
		throw std::exception("Error: could not get texture info");

	m_height = info.Height;
	m_width = info.Width;
}
void Wilt::Texture::Shutdown()
{
	if (m_texture)
	{
		m_texture->Release();
		m_texture = NULL;
	}
}

// Accessor functions
unsigned int Wilt::Texture::GetHeight()
{
	return m_height;
}
unsigned int Wilt::Texture::GetWidth()
{
	return m_width;
}
ID3D11ShaderResourceView* Wilt::Texture::GetTexture()
{
	return m_texture;
}