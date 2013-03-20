// FILE: Font.h
// DATE: 2/27/13 - 3/18/13
// DESC: declaration of the object to manage a font

#pragma once
namespace Wilt { class Font; }

#include <d3d11.h>
#include <d3dx10math.h>
#include <fstream>

#include "graphicsobject.h"
#include "Texture.h"
#include "Text.h"

namespace Wilt
{
	class Font
	{
	private:
		struct VertexType
		{
			D3DXVECTOR3 position;
			D3DXVECTOR2 texture;
		};
		
		float* m_fontData;
		Texture* m_texture;

	public:
		Font();
		~Font();

		void Initialize(ID3D11Device* device, char* fontFilename, WCHAR* textureFilename);
		void RenderText(GraphicsObject* graphics, Text* textobject);
		void Shutdown();

		ID3D11ShaderResourceView* GetTexture();
		void BuildArrays(void* vertices, unsigned int* indices, const char* text);
	}; 
}
