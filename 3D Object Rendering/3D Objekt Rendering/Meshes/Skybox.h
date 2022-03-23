#pragma once
#include "Mesh.h"
#include "../Camera.h"
#include "../DirLight.h"

/// <summary>
/// An object for a skybox.
/// </summary>
class Skybox : public Mesh
{
	public:
		/// <summary>
		/// The constructor of the skybox.
		/// </summary>
		/// <param name="device">The d3d device of the application.</param>
		/// <param name="mat">The material of the skybox.</param>
		/// <param name="camera">The camera object of the application.</param>
		/// <param name="vertices">A list of the vertices that the skybox is supposed to have.</param>
		/// <param name="indices">A list of the indices that the skybox is supposed to have.</param>
		/// <param name="dirLight">The light source of the application.</param>
		/// <param name="position">The start position of the skybox.</param>
		/// <param name="rotation">The start rotation of the skybox.</param>
		/// <param name="scale">The start scale of the skybox.</param>
		Skybox(ID3D11Device* device, Material* mat, Camera* camera, vector<Vertex>* vertices, vector<short>* indices, DirLight* dirLight, XMFLOAT3 position, XMFLOAT3 rotation, XMFLOAT3 scale) : Mesh(device, mat, vertices, indices, position, rotation, scale) 
		{ 
			this->camera = camera; 
			this->dirLight = dirLight; 
		}

		/// <summary>
		/// Updates the skybox every frame, aligns it with the players position and rotates it with the light direction.
		/// </summary>
		/// <param name="deltaTime">The time that has passed since the last frame.</param>
		virtual void Update(float deltaTime);

	private:
		/// <summary>The camera object of the application.</summary>
		Camera* camera;
		/// <summary>The light source of the application.</summary>
		DirLight* dirLight;
};