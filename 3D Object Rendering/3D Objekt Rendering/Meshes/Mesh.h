#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include <xutility>
#include "../Utility/Vertex.h"
#include "../Material.h"
#include "../Utility/Util.h"
#include "../Utility/File.h"

using namespace DirectX;

/// <summary>
/// An object that represents a world object in space as well as it's mesh.
/// </summary>
class Mesh
{
	public:
		/// <summary>
		/// A buffer that contains the meshes matrix for vertex shaders.
		/// </summary>
		struct MeshBuffer { XMFLOAT4X4 Matrix; };

		/// <summary>
		/// An empty constructor that exists for overriding purposes.
		/// </summary>
		Mesh() {};

		/// <summary>
		/// The constructor of the mesh.
		/// </summary>
		/// <param name="device">The d3d device of the application.</param>
		/// <param name="mat">The material that the mesh is supposed to have.</param>
		/// <param name="vertices">A list of the vertices that the mesh is supposed to have.</param>
		/// <param name="indices">A list of the indices that the mesh is supposed to have.</param>
		/// <param name="position">The start position of the mesh.</param>
		/// <param name="rotation">The start rotation of the mesh.</param>
		/// <param name="scale">The start scale of the mesh.</param>
		Mesh(ID3D11Device* device, Material* mat, vector<Vertex>* vertices, vector<short>* indices, XMFLOAT3 position, XMFLOAT3 rotation, XMFLOAT3 scale);

		/// <summary>
		/// Renders the mesh and it's material every frame.
		/// </summary>
		/// <param name="context">The d3d device context of the application.</param>
		/// <param name="currentMatID">The ID of the currently rendered material.</param>
		void Render(ID3D11DeviceContext* context, int* currentMatID);

		/// <summary>
		/// Updates the mesh every frame.
		/// </summary>
		/// <param name="deltaTime">The time that has passed since the last frame.</param>
		virtual void Update(float deltaTime);

		/// <summary>The current position of the mesh.</summary>
		XMFLOAT3 Position;
		/// <summary>The current rotation of the mesh.</summary>
		XMFLOAT3 Rotation;
		/// <summary>The current scale of the mesh.</summary>
		XMFLOAT3 Scale;

		/// <summary>The material of the mesh.</summary>
		Material* Mat;

	protected:
		/// <summary>
		/// Creates the vertex buffer for the mesh.
		/// </summary>
		/// <param name="device">The d3d device of the application.</param>
		/// <param name="vertices">The vertices that are loaded.</param>
		virtual void SetVertecies(ID3D11Device* device, vector<Vertex> vertices);

		/// <summary>
		/// Creates the index buffer for the mesh.
		/// </summary>
		/// <param name="device">The d3d device of the application.</param>
		/// <param name="indices">The indices that are loaded.</param>
		virtual void SetIndices(ID3D11Device* device, vector<short> indices);

		/// <summary>
		/// Updates the matrix of the mesh.
		/// </summary>
		void UpdateMatrix();

		/// <summary>
		/// Initializes the mehs buffer.
		/// </summary>
		/// <param name="device">The d3d device of the application.</param>
		void InitBuffer(ID3D11Device* device);

		/// <summary>The transform matrix of the mesh.</summary>
		XMFLOAT4X4 matrix = {};

		/// <summary>The buffer that contains the meshes vertices.</summary>
		ID3D11Buffer* vertexBuffer = nullptr;
		/// <summary>The buffer that contains the meshes indices.</summary>
		ID3D11Buffer* indexBuffer = nullptr;

		/// <summary>The shader buffer of the mesh.</summary>
		ID3D11Buffer* meshBuffer = nullptr;

		/// <summary>The meshes vertex count.</summary>
		UINT vertexCount = 0;
		/// <summary>The size of a vertex struct.</summary>
		UINT vertexStride = 0;			
		/// <summary>The meshes index count.</summary>
		UINT indexCount = 0;
};