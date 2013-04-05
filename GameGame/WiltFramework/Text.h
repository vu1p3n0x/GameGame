// FILE: Text.h
// DATE: 2/25/13
// DESC: declaration of the class to manage an object of text

#pragma once
namespace Wilt { class Text; }

#include <string>

#include "graphicsobject.h"
#include "Font.h"

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
		float m_red, m_blue, m_green;
		bool m_recreate;

		float m_positionX;
		float m_positionY;
		float m_rotation;
		float m_scaleX;
		float m_scaleY;
		float m_originX;
		float m_originY;

		friend class Font;

		void Recreate(GraphicsObject* graphics, Font* font);

	public:
		Text();
		~Text();

		/// <summary> Initializes the text from a string and position </summary>
		bool Initialize(GraphicsObject* graphics, Wilt::Font* font, std::string text);
		void Shutdown();

		D3DXMATRIX GetTransformation();
		float GetHeight();
		float GetWidth();

		void SetText(std::string text);
		void SetPosition(float positionX, float positionY);
	}; 
}