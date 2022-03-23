#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include "Utility/WICTextureLoader.h"
#include <d3dcompiler.h>
#include <string>

#pragma comment(lib, "d3dcompiler.lib")

using namespace DirectX;
using namespace std;

/// <summary>
/// An object for a material.
/// </summary>
class Material
{
	public:
		/// <summary>
		/// A buffer that contains information about the material.
		/// </summary>
		struct MaterialBuffer { float SpecularPower; float Glossy; XMFLOAT2 Empty; };

		/// <summary>
		/// The constructor of the material.
		/// </summary>
		/// <param name="id">The ID of the material</param>
		/// <param name="device"The d3d device of the application.></param>
		/// <param name="vertexShaderName">The file name of the vertex shader.</param>
		/// <param name="pixelShaderName">The file name of the pixel shader.</param>
		/// <param name="textureName">The file name of the texture.</param>
		/// <param name="bufferData">Data for the material buffer.</param>
		Material(int id, ID3D11Device* device, wstring vertexShaderName, wstring pixelShaderName, wstring textureName, MaterialBuffer bufferData);

		/// <summary>
		/// Renders the materials resources every frame.
		/// </summary>
		/// <param name="context">The d3d device context of the application.</param>
		void Render(ID3D11DeviceContext* context);

		/// <summary>The ID of the material.</summary>
		int ID;

	private:
		/// <summary>The materials vertex shader.</summary>
		ID3D11VertexShader* vertexShader = nullptr;
		/// <summary>The materials pixel shader.</summary>
		ID3D11PixelShader* pixelShader = nullptr;
		/// <summary>The materials input layout.</summary>
		ID3D11InputLayout* inputLayout = nullptr;
		/// <summary>The materials blend state.</summary>
		ID3D11BlendState* blendState = nullptr;

		/// <summary>The shader buffer of the material.</summary>
		ID3D11Buffer* materialBuffer = nullptr;

		/// <summary>The texture of the material.</summary>
		ID3D11ShaderResourceView* texture = nullptr;
		/// <summary>The materials sampler state.</summary>
		ID3D11SamplerState* samplerState = nullptr;
};