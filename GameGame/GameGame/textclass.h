// FILE: textclass.h
// DATE: 2/25/13
// DESC: declaration of the class to manage text

#ifndef TEXTCLASS_H
#define TEXTCLASS_H

#include "fontclass.h"
#include "fontshaderclass.h"

class TextClass
{
public:
	TextClass();
	TextClass(const TextClass&);
	~TextClass();

	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, HWND, int, int, D3DXMATRIX);
	void Shutdown();
	bool Render(ID3D11DeviceContext*, D3DXMATRIX, D3DXMATRIX);

private:
	struct SentenceType
	{
		ID3D11Buffer* vertexBuffer, * indexBuffer;
		int vertexCount, indexCount, maxLength;
		float red, green, blue;
	};
	struct VertexType
	{
		D3DXVECTOR3 position;
		D3DXVECTOR2 texture;
	};

	FontClass* m_font;
	FontShaderClass* m_fontShader;
	int m_screenWidth, m_screenHeight;
	D3DXMATRIX m_baseViewMatrix;
	SentenceType* m_sentence;

	bool InitializeSentence(SentenceType**, int, ID3D11Device*);
	bool UpdateSentence(SentenceType*, char*, int, int, float, float, float, ID3D11DeviceContext*);
	void ReleaseSentence(SentenceType**);
	bool RenderSentence(ID3D11DeviceContext*, SentenceType*, D3DXMATRIX, D3DXMATRIX);
};

#endif