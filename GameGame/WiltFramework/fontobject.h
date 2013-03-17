// FILE: fontobject.h
// DATE: 2/27/13
// DESC: declaration of the object to manage a font

#pragma once
namespace Wilt { class FontObject; }

#include <d3d11.h>
#include <d3dx10math.h>
#include <fstream>

#include "graphicsobject.h"
#include "textureclass.h"
#include "text.h"

namespace Wilt
{
	class FontObject
	{
	private:
		struct FontType
		{
			float left;
			float right;
			int size;
		};
		struct VertexType
		{
			D3DXVECTOR3 position;
			D3DXVECTOR2 texture;
		};

		FontType* m_font;
		TextureClass* m_texture;

	public:
		FontObject();
		FontObject(const FontObject& fontobject);
		~FontObject();

		bool Initialize(ID3D11Device* device, char* fontFilename, WCHAR* textureFilename);
		void RenderText(GraphicsObject* graphics, Text* textobject);
		void Shutdown();

		ID3D11ShaderResourceView* GetTexture();
		void BuildVertexArray(void* vertices, const char* text, float positionX, float positionY);
	}; 
}
