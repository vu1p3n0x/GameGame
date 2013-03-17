// FILE: textobject.h
// DATE: 2/25/13
// DESC: declaration of the class to manage an object of text

#ifndef TEXTOBJECT_H
#define TEXTOBJECT_H

#include <string>

#include "graphicsobject.h"
#ifndef FONTOBJECT_H
class FontObject;
#endif

class TextObject
{
private:
	struct VertexType
	{
		D3DXVECTOR3 position;
		D3DXVECTOR2 texture;
	};

	std::string m_text;
	ID3D11Buffer* m_vertexBuffer;
	ID3D11Buffer* m_indexBuffer;
	int m_vertexCount;
	int m_indexCount;
	float m_positionX, m_positionY;
	float m_red, m_blue, m_green;
	bool m_recreate;

	friend class FontObject;

	void Recreate(GraphicsObject* graphics, FontObject* font);

public:
	TextObject();
	TextObject(const TextObject& textobject);
	~TextObject();

	bool Initialize(GraphicsObject* graphics, std::string text, float positionX, float positionY);
	void Shutdown();

	void SetText(std::string text);
	void SetPosition(float positionX, float positionY);
};

#include "fontobject.h"

#endif