#include "DirLight.h"

DirLight::DirLight(ID3D11Device* device, LightBuffer lightData, Input* input)
{
    this->input = input;
    LightData = lightData;

    D3D11_BUFFER_DESC desc = {};
    desc.ByteWidth = sizeof(LightBuffer);
    desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    desc.Usage = D3D11_USAGE_DYNAMIC;
    desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    
    device->CreateBuffer(&desc, nullptr, &lightBuffer);
}

void DirLight::Render(ID3D11DeviceContext* context)
{
	D3D11_MAPPED_SUBRESOURCE data = {};

	context->Map(lightBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &data);
	LightBuffer* lightBuffer = static_cast<LightBuffer*>(data.pData);

    lightBuffer->AmbientColor = LightData.AmbientColor;
    lightBuffer->Color = LightData.Color;
    lightBuffer->Direction = LightData.Direction;
    lightBuffer->Intensity = LightData.Intensity;
    lightBuffer->Rotation = LightData.Rotation;

	context->Unmap(this->lightBuffer, 0);
    context->PSSetConstantBuffers(0, 1, &this->lightBuffer);
}

void DirLight::Update(float deltaTime)
{
    LightData.Rotation += input->QEAxis * deltaTime;

    while (LightData.Rotation > XM_PI * 2) LightData.Rotation -= XM_PI * 2;
    while (LightData.Rotation < 0) LightData.Rotation += XM_PI * 2;

    LightData.Direction = {sin(LightData.Rotation), -0.5f, cos(LightData.Rotation)};
}