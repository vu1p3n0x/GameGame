// FILE: fontclass.h
// DATE: 2/24/13
// DESC: declaration of the class to manage fonts

#ifndef FONTCLASS_H
#define FONTCLASS_H

#include <d3d11.h>
#include <d3dx10math.h>
#include <fstream>
#include "textureclass.h"

class FontClass
{
public:
	FontClass();
	FontClass(const FontClass&);
	~FontClass();

	bool Initialize(ID3D11Device*, char*, WCHAR*);
	void Shutdown();

	ID3D11ShaderResourceView* GetTexture();
	void BuildVertexArray(void*, const char*, float, float);

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

	bool LoadFontData(char*);
	void ReleaseFontData();
	bool LoadTexture(ID3D11Device*, WCHAR*);
	void ReleaseTexture();
};

#endif