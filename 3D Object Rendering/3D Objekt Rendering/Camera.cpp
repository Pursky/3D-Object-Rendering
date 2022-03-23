#include "Camera.h"

Camera::Camera(ID3D11Device* device, int width, int height, Input* input, XMFLOAT3 position, XMFLOAT2 rotation)
{
	this->input = input;

	Position = position;
	Rotation = rotation;

	Forward =	{ 0.0f, 0.0f, 1.0f };
	Right	=	{ 1.0f, 0.0f, 0.0f };
	Up		=	{ 0.0f, 1.0f, 0.0f };

	XMMATRIX matrix = XMMatrixLookToLH(
		XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f),
		XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f),
		XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)
	);
	XMStoreFloat4x4(reinterpret_cast<XMFLOAT4X4*>(&Matrix), matrix);
	XMMATRIX projectionMatrix = XMMatrixPerspectiveFovLH(
		XM_PI * 0.3333333f,                                                     
		static_cast<FLOAT>(width) / static_cast<FLOAT>(height),
		0.3f, 1000.0f                                                           
	);
	XMStoreFloat4x4(&ProjectionMatrix, projectionMatrix);

	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.ByteWidth = sizeof(CameraBuffer);
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	device->CreateBuffer(&bufferDesc, nullptr, &cameraBuffer);
}

void Camera::Update(float deltaTime)
{
	float rotationSpeed = 2;

	Rotation.x += input->DeltaMouse.y * rotationSpeed;
	Rotation.y += input->DeltaMouse.x * rotationSpeed;

	UpdateMatrix();
}

void Camera::Render(ID3D11DeviceContext* context)
{
	D3D11_MAPPED_SUBRESOURCE data = {};
	context->Map(cameraBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &data);

	XMMATRIX vMatrix = XMLoadFloat4x4(&Matrix);
	XMMATRIX pMatrix = XMLoadFloat4x4(&ProjectionMatrix);

	XMMATRIX camMatrix = XMMatrixTranspose(vMatrix * pMatrix);

	CameraBuffer* cameraBuffer = static_cast<CameraBuffer*>(data.pData);

	cameraBuffer->Position = Position;
	XMStoreFloat4x4(&(cameraBuffer->CamMatrix), camMatrix);
	
	context->Unmap(this->cameraBuffer, 0);
	
	context->VSSetConstantBuffers(1, 1, &this->cameraBuffer);
}

void Camera::UpdateMatrix()
{
	while (Rotation.x > XM_PI * 0.49f) Rotation.x = XM_PI * 0.49f;
	while (Rotation.x < -XM_PI * 0.49f) Rotation.x = -XM_PI * 0.49f;
	
	while (Rotation.y > XM_PI * 2) Rotation.y -= XM_PI * 2;
	while (Rotation.y < 0) Rotation.y += XM_PI * 2;

	XMMATRIX rotationMatrix = XMMatrixRotationRollPitchYaw(Rotation.x, Rotation.y, 0);

	XMVECTOR forward =	{ 0.0f, 0.0f, 1.0f };
	XMVECTOR right =	{ 1.0f, 0.0f, 0.0f };
	XMVECTOR up =		{ 0.0f, 1.0f, 0.0f };

	forward = XMVector3Transform(forward, rotationMatrix);
	right = XMVector3Transform(right, rotationMatrix);
	up = XMVector3Transform(up, rotationMatrix);

	Forward = { XMVectorGetX(forward), XMVectorGetY(forward), XMVectorGetZ(forward) };
	Right = { XMVectorGetX(right), XMVectorGetY(right), XMVectorGetZ(right) };
	Up = { XMVectorGetX(up), XMVectorGetY(up), XMVectorGetZ(up) };

	XMMATRIX matrix = XMMatrixLookToLH(
		XMVectorSet(Position.x, Position.y, Position.z, 0.0f),
		XMVectorSet(Forward.x, Forward.y, Forward.z, 0.0f),
		XMVectorSet(Up.x, Up.y, Up.z, 0.0f)
	);
	XMStoreFloat4x4(reinterpret_cast<XMFLOAT4X4*>(&Matrix), matrix);
}
