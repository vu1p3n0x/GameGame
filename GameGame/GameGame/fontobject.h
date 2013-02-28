// FILE: fontobject.h
// DATE: 2/27/13
// DESC: declaration of the object to manage a font

#ifndef FONTOBJECT_H
#define FONTOBJECT_H

#include <d3d11.h>
#include <d3dx10math.h>
#include <fstream>

#include "graphicsobject.h"
#include "textureclass.h"

#ifndef TEXTOBJECT_H
class TextObject;
#endif

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
	FontObject(ID3D11Device* device, char* fontFilename, WCHAR* textureFilename);
	FontObject(const FontObject& fontobject);
	~FontObject();

	ID3D11ShaderResourceView* GetTexture();
	void BuildVertexArray(void* vertices, const char* text, float positionX, float positionY);
	void RenderText(GraphicsObject* graphics, TextObject* textobject);
};

#include "textobject.h"

#endif