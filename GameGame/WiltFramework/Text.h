// FILE: Text.h
// DATE: 2/25/13
// DESC: declaration of the class to manage an object of text

#pragma once
namespace Wilt { class Text; }

#include <string>

#include "graphicsobject.h"
#include "fontobject.h"

namespace Wilt
{
	class Text
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
		Text();
		Text(const Text& Text);
		~Text();

		bool Initialize(GraphicsObject* graphics, std::string text, float positionX, float positionY);
		void Shutdown();

		void SetText(std::string text);
		void SetPosition(float positionX, float positionY);
	}; 
}