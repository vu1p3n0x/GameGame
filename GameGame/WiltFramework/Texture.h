// FILE: Texture.h
// DATE: 2/22/13 - 3/18/13
// DESC: declaration of the texture class to represent a texture

#pragma once
namespace Wilt { class Texture; }

#include <d3d11.h>
#include <d3dx11tex.h>
#include <exception>

namespace Wilt
{
	class Texture
	{
	private:
		ID3D11ShaderResourceView* m_texture;
		unsigned int m_height;
		unsigned int m_width;

	public:
		Texture();
		~Texture();

		void Initialize(ID3D11Device*, WCHAR*);
		void Shutdown();

		unsigned int GetWidth();
		unsigned int GetHeight();
		ID3D11ShaderResourceView* GetTexture();
	}; 
}