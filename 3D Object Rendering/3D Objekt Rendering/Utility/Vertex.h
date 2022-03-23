#pragma once
#include <d3d11.h>
#include <DirectXMath.h>

using namespace DirectX;

/// <summary>
/// A struct for the vertex buffer.
/// </summary>
struct Vertex
{
	public:
		/// <summary>The vertex position.</summary>
		XMFLOAT3 Position;
		/// <summary>The vertex normal.</summary>
		XMFLOAT3 Normal;
		/// <summary>The vertex uv position.</summary>
		XMFLOAT2 UV;
		/// <summary>An empty float, necessary for the buffer to have the right size.</summary>
		float buffer = 0;

		/// <summary>
		/// A default vertex constructor for the vertex.
		/// </summary>
		Vertex() : Position(1.0f, 1.0f, 1.0f), Normal(0.0f, 0.0f, 0.0f), UV(0.0f, 0.0f) {}

		/// <summary>
		/// A vertex constructor that passes a position.
		/// </summary>
		/// <param name="x">The x position.</param>
		/// <param name="y">The y position.</param>
		/// <param name="z">The z position.</param>
		Vertex(float x, float y, float z) : Position(x, y, z), Normal(0.0f, 0.0f, 0.0f), UV(0.0f, 0.0f) {}

		/// <summary>
		/// A vertex constructor that passes a position and a normal.
		/// </summary>
		/// <param name="x">The x position.</param>
		/// <param name="y">The y position.</param>
		/// <param name="z">The z position.</param>
		/// <param name="nx">The x value of the normal.</param>
		/// <param name="ny">The y value of the normal.</param>
		/// <param name="nz">The z value of the normal.</param>
		Vertex(float x, float y, float z, float nx, float ny, float nz) : Position(x, y, z), Normal(nx, ny, nz), UV(0.0f, 0.0f) {}

		/// <summary>
		/// A vertex constructor that passes a position, a normal and a uv position.
		/// </summary>
		/// <param name="x">The x position.</param>
		/// <param name="y">The y position.</param>
		/// <param name="z">The z position.</param>
		/// <param name="nx">The x value of the normal.</param>
		/// <param name="ny">The y value of the normal.</param>
		/// <param name="nz">The z value of the normal.</param>
		/// <param name="u">The x value of the uv position.</param>
		/// <param name="v">The y value of the uv position.</param>
		Vertex(float x, float y, float z, float nx, float ny, float nz, float u, float v) : Position(x, y, z), Normal(nx, ny, nz), UV(u, v) {}
};