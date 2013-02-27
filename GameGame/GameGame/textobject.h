// FILE: textobject.h
// DATE: 2/25/13
// DESC: declaration of the class to manage an object of text

#ifndef TEXTOBJECT_H
#define TEXTOBJECT_H

#include "fontclass.h"
#include "fontshaderclass.h"

class TextObject
{
private:
	FontClass* m_font;
	FontShaderClass* m_fontShader;
	string m_text;
	ID3D11Buffer* m_vertexBuffer;
	ID3D11Buffer* m_indexBuffer;
	int m_vertexCount;
	int m_indexCount;
	float m_red, m_blue, m_green;

public:
	TextObject();
	TextObject(const TextObject& textobject);
	~TextObject();

	bool Initialize(ID3D11Device* device, FontClass* font, string text, float positionX, float positionY);
	bool Render();
	void Shutdown();

	void SetFont(FontClass* font);
	void SetText(string text);
	void SetPosition(float positionX, float positionY);
};

#endif