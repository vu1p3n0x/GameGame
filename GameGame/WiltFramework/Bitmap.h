// FILE: Bitmap.h
// DATE: 3/6/13
// DESC: declaration of a class to manage a 2D image

#pragma once
namespace Wilt { class Bitmap; }

#include <d3d11.h>
#include <d3dx10math.h>

#include "Texture.h"
#include "graphicsobject.h"

namespace Wilt
{
	class Bitmap
	{
	private:
		struct VertexType
		{
			D3DXVECTOR3 position;
			D3DXVECTOR2 texture;
		};

		void InitializeBuffers(ID3D11Device* device);

		ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
		Texture *m_texture;

		int m_screenWidth, m_screenHeight;
		int m_bitmapWidth, m_bitmapHeight;

		D3DXMATRIX m_position;
		D3DXMATRIX m_rotation;
		D3DXMATRIX m_scale;
		D3DXMATRIX m_origin;

		static const unsigned short VERTEXCOUNT = 4;
		static const unsigned short INDEXCOUNT = 6;

	public:
		Bitmap();
		~Bitmap();

		/// <summary> Initializes the Bitmap by loading the texture and sets up graphics elements </summary>
		/// <param name="graphics"> A pointer to the GraphicsObject used to render the texture </param>
		/// <param name="textureFilename"> The file location of the texture to be loaded </param>
		/// <param name="bitmapWidth"> The width of the texture </param>
		/// <param name="bitmapHeight"> The height of the texture </param>
		/// <exception cref="std::exception"> </exception>
		/// <remarks>
		/// Gets the needed information from the graphics object in order to render the texture properly as well as creates
		/// vertex and index buffers for the texture, also loads the texture as sets default values for scale, rotation,
		/// and position
		/// </remarks>
		void Initialize(GraphicsObject* graphics, WCHAR* textureFilename, unsigned int bitmapWidth, unsigned int bitmapHeight);
		/// <summary> Renders the texture to the screen based on the scale, rotation, and position specified </summary>
		/// <param name="graphics"> A pointer to the GraphicsObject used to render the texture </param>
		/// <remarks>
		/// Applies transformations and draws the texture to the screen
		/// </remarks>
		void Render(GraphicsObject* graphics);
		/// <summary> Releases graphics assets and deletes variables </summary>
		/// <remarks>
		/// Releases and deletes vertex and index buffers as well as the texture used.
		/// </remarks>
		void Shutdown();

		/// <summary> Gets the transformation matrix used to draw the texture </summary>
		/// <remarks>
		/// Is the combination of origin, scale, rotation, and position matrices
		/// </remarks>
		D3DXMATRIX GetTransformation();

		/// <summary> Moves the texture to the specified screen coordinate </summary>
		/// <param name="positionX"> X location to render the texture </param>
		/// <param name="positionY"> Y location to render the texture </param>
		/// <remarks>
		/// Sets the XY position to render the texture to. Coordinate system is centered in the bottom left corner of the
		/// graphical window and steps in screen pixels. 
		/// </remarks>
		void SetPosition(float positionX, float positionY);
		/// <summary> Sets the size of the texture in scale from the default </summary>
		/// <param name="scale"> Value from 0.0f to inf to scale the texture where 1.0f is the default </param>
		/// <exception cref="std::exception"> Thrown when scale value is less than 0.0f </exception>
		/// <remarks>
		/// Scales the texture the the specified amount (i.e. 2.0f is twice as big whereas 0.5f is half as big). Range
		/// exception will be thrown for negative values but not 0.0f (texture will not be drawn)
		/// </remarks>
		void SetScale(float scale);
		/// <summary> Sets the size of the texture in scale from the default in the X and Y direction </summary>
		/// <param name="scaleX"> Value from 0.0f to inf to scale the texture in the X direction where 1.0f is the default </param>
		/// <param name="scaleY"> Value from 0.0f to inf to scale the texture in the Y direction where 1.0f is the default </param>
		/// <exception cref="std::exception"> Thrown when scale value is less than 0.0f </exception>
		/// <remarks>
		/// Scales the texture the the specified amount (i.e. 2.0f is twice as big whereas 0.5f is half as big). Range
		/// exception will be thrown for negative values but not 0.0f (texture will not be drawn). Scaling is applied
		/// before rotation and position but after the origin application
		/// </remarks>
		void SetScale(float scaleX, float scaleY);
		/// <summary> Rotates the texture around the specified origin by the rotation in radians </summary>
		/// <param name="rotation"> Value to rotate the texture in radians CCW </param>
		/// <remarks>
		/// Rotates the texture around the specified origin by the rotation in radians
		/// </remarks>
		void SetRotation(float rotation);
		/// <summary> Sets the position in texture coordinates that is defined as the origin </summary>
		/// <param name="offsetX"> Sets the X position of the origin in terms of texture coordidnates (0.0f - 1.0f) </param>
		/// <param name="offsetY"> Sets the Y position of the origin in terms of texture coordidnates (0.0f - 1.0f) </param>
		/// <remarks>
		/// Texture coordinates are centered 0,0 at the top-left corner (i.e. to have the origin centered on the texture pass 
		/// 0.5,0.5 as the offsets)
		/// </remarks>
		void SetOrigin(float offsetX, float offsetY);
	}; 
}