#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include "Direct3D.h"
#include "Utility/Input.h"

using namespace DirectX;

/// <summary>
/// An object for a directional light.
/// </summary>
class DirLight
{
	public:
		/// <summary>
		/// A buffer that contains information about the light in the scene.
		/// </summary>
		struct LightBuffer { XMFLOAT3 Direction; float Intensity; XMFLOAT4 Color; XMFLOAT4 AmbientColor; float Rotation; XMFLOAT3 empty; };

		/// <summary>
		/// The constructor of the directional light.
		/// </summary>
		/// <param name="device">The d3d device of the application.</param>
		/// <param name="lightData">Initial data for the directional light.</param>
		/// <param name="input">The input object of the application.</param>
		DirLight(ID3D11Device* device, LightBuffer lightData, Input* input);

		/// <summary>
		/// Updates the light buffer every frame.
		/// </summary>
		/// <param name="context">The d3d device context of the application.</param>
		void Render(ID3D11DeviceContext* context);

		/// <summary>
		/// Updates the directional light every frame.
		/// </summary>
		/// <param name="deltaTime">The time that has passed since the last frame.</param>
		void Update(float deltaTime);

		/// <summary>The current light data.</summary>
		LightBuffer LightData;

	private:
		/// <summary>The shader buffer of the directional light.</summary>
		ID3D11Buffer* lightBuffer = nullptr;
		/// <summary>The input object of the application.</summary>
		Input* input = nullptr;
};