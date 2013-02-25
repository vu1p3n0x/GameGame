// FILE: font.vs
// DATE: 2/24/13
// DESC: vertex shader for drawing fonts

cbuffer PerFrameBuffer
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
};

struct VertexInputType
{
	float4 position : POSITION;
	float2 tex: TEXCOORD0;
};
struct PixelOutputType
{
	float position : SV_POSITION;
	float2 tex : TEXCOORD0;
};

PixelOutputType FontVertexShader(VertexInputType input)
{
	PixelOutputType output;

	input.position.w = 1.0f;

	output.position = mul(input.position, worldMatrix);
	output.position = mul(output.position, viewMatrix);
	output.position = mul(output.position, projectionMatrix);

	output.tex = input.tex;

	return output;
}