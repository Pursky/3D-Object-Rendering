#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include "Utility/Util.h"
#include "Utility/Input.h"

using namespace DirectX;

/// <summary>
/// An object that represents a camera.
/// </summary>
class Camera
{
	public:
		/// <summary>
		/// A buffer that contains a combined camera matrix and the cameras world position.
		/// </summary>
		struct CameraBuffer { XMFLOAT4X4 CamMatrix; XMFLOAT3 Position; float empty; };

		/// <summary>
		/// The constructor of the camera.
		/// </summary>
		/// <param name="device">The d3d device of the application.</param>
		/// <param name="width">The pixel width of the window.</param>
		/// <param name="height">The pixel height of the window.</param>
		/// <param name="input">The input object of the application.</param>
		/// <param name="position">The start position of the camera.</param>
		/// <param name="rotation">The start rotation of the camera.</param>
		Camera(ID3D11Device* device, int width, int height, Input* input, XMFLOAT3 position, XMFLOAT2 rotation);

		/// <summary>
		/// Updates the camera every frame and handles mouse movement.
		/// </summary>
		/// <param name="deltaTime">The time that has passed since the last frame.</param>
		void Update(float deltaTime);

		/// <summary>
		/// Updates the camera vuffer every frame.
		/// </summary>
		/// <param name="context">The d3d device context of the application.</param>
		void Render(ID3D11DeviceContext* context);

		/// <summary>The current position of the camera.</summary>
		XMFLOAT3 Position;
		/// <summary>The current rotation of the camera.</summary>
		XMFLOAT2 Rotation;

		/// <summary>The forward vector of the camera.</summary>
		XMFLOAT3 Forward;
		/// <summary>The right vector of the camera.</summary>
		XMFLOAT3 Right;
		/// <summary>The up vector of the camera.</summary>
		XMFLOAT3 Up;
			
		/// <summary>The view matrix of the camera.</summary>
		XMFLOAT4X4 Matrix = {};
		/// <summary>The projection matrix of the camera.</summary>
		XMFLOAT4X4 ProjectionMatrix = {};

	private:
		/// <summary>
		/// Updates the view matrix of the mesh.
		/// </summary>
		void UpdateMatrix();

		/// <summary>The input object of the application.</summary>
		Input* input;
		/// <summary>The shader buffer of the camera.</summary>
		ID3D11Buffer* cameraBuffer = nullptr;
};