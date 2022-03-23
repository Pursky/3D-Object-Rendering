#pragma once
#include "Mesh.h"

/// <summary>
/// An object for an automatically generated UV sphere.
/// </summary>
class Sphere : public Mesh
{
	public:
		/// <summary>
		/// The constructor of the sphere.
		/// </summary>
		/// <param name="device">The d3d device of the application.</param>
		/// <param name="mat">The material that the sphere is supposed to have.</param>
		/// <param name="resolution">The amount of vertices the sphere has in half an equator.</param>
		/// <param name="inverse">Whether the sphere is inverse or not.</param>
		/// <param name="position">The start position of the mesh</param>
		/// <param name="rotation">The start rotation of the mesh</param>
		/// <param name="scale">The start scale of the mesh</param>
		Sphere(ID3D11Device* device, Material* mat, int resolution, bool inverse, XMFLOAT3 position, XMFLOAT3 rotation, XMFLOAT3 scale);

		/// <summary>
		/// Updates the sphere every frame.
		/// </summary>
		/// <param name="deltaTime">The time that has passed since the last frame.</param>
		virtual void Update(float deltaTime);

	private:
		/// <summary>
		/// Generates the vertices for the sphere and creates the vertex buffer.
		/// </summary>
		/// <param name="device">The d3d device of the application.</param>
		void SetVertecies(ID3D11Device* device);

		/// <summary>
		/// Generates the indices for the sphere and creates the index buffer.
		/// </summary>
		/// <param name="device">The d3d device of the application.</param>
		void SetIndices(ID3D11Device* device);

		/// <summary>The amount of vertices the sphere has in half an equator.</summary>
		int resolution;
		/// <summary>Whether the sphere is inverse or not.</summary>
		bool inverse;
};