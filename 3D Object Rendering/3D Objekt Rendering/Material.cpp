#include "Material.h"

Material::Material(int id, ID3D11Device* device, wstring vertexShaderName, wstring pixelShaderName, wstring textureName, MaterialBuffer bufferData)
{
	ID = id;

	// Create Vertex Shader.

	ID3DBlob* vertexShaderCode = nullptr;
	D3DReadFileToBlob((L"Resources/Shaders/" + vertexShaderName).c_str(), &vertexShaderCode);

	device->CreateVertexShader(vertexShaderCode->GetBufferPointer(), vertexShaderCode->GetBufferSize(), nullptr, &vertexShader);

	// Create Input Layout.
	D3D11_INPUT_ELEMENT_DESC elements[3] = {};

	elements[0].SemanticName = "POSITION";
	elements[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;

	elements[1].SemanticName = "NORMAL";
	elements[1].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	elements[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;

	elements[2].SemanticName = "TEXCOORD";
	elements[2].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	elements[2].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;

	device->CreateInputLayout(elements, 3, vertexShaderCode->GetBufferPointer(), vertexShaderCode->GetBufferSize(), &inputLayout);

	vertexShaderCode->Release();

	// Create Blend State.
	D3D11_BLEND_DESC blendDesc = {};
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	blendDesc.RenderTarget[0].BlendEnable = TRUE;

	device->CreateBlendState(&blendDesc, &blendState);

	// Create Pixel Shader.

	ID3DBlob* pixelShaderCode = nullptr;
	D3DReadFileToBlob((L"Resources/Shaders/" + pixelShaderName).c_str(), &pixelShaderCode);

	device->CreatePixelShader(pixelShaderCode->GetBufferPointer(), pixelShaderCode->GetBufferSize(), nullptr, &pixelShader);

	pixelShaderCode->Release();

	// Create Material Buffer.

	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.ByteWidth = sizeof(MaterialBuffer);
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.Usage = D3D11_USAGE_IMMUTABLE;

	D3D11_SUBRESOURCE_DATA data = {};
	data.pSysMem = &bufferData;

	device->CreateBuffer(&bufferDesc, &data, &materialBuffer);

	// Create Texture and Sampler.

	if (textureName._Equal(L"")) textureName = L"White.png";
	CreateWICTextureFromFile(device, (L"Resources/Textures/" + textureName).c_str(), nullptr, &texture);
	
	D3D11_SAMPLER_DESC samplerDesc = {};
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	
	device->CreateSamplerState(&samplerDesc, &samplerState);
}

void Material::Render(ID3D11DeviceContext* context)
{
	context->PSSetShaderResources(0, 1, &texture);
	context->PSSetSamplers(0, 1, &samplerState);

	context->OMSetBlendState(blendState, 0, 0xffffffff);
	context->VSSetShader(vertexShader, nullptr, 0);
	context->PSSetShader(pixelShader, nullptr, 0);
	context->IASetInputLayout(inputLayout);

	context->PSSetConstantBuffers(1, 1, &this->materialBuffer);
}
