#include "Mesh.h"

Mesh::Mesh(ID3D11Device* device, Material* mat, vector<Vertex>* vertices, vector<short>* indices, XMFLOAT3 position, XMFLOAT3 rotation, XMFLOAT3 scale)
{
	if (scale.x == 0 && scale.y == 0 && scale.z == 0) scale = { 1.0f, 1.0f, 1.0f };

	Position = position;
	Rotation = rotation;
	Scale = scale;

	Mat = mat;

	SetVertecies(device, *vertices);
	SetIndices(device, *indices);

	XMStoreFloat4x4(&matrix, XMMatrixIdentity());

	InitBuffer(device);
}

void Mesh::Render(ID3D11DeviceContext* context, int* currentMatID)
{
	if (Mat->ID != *currentMatID) 
	{
		Mat->Render(context);
		*currentMatID = Mat->ID;
	}

	XMMATRIX mMatrix = XMLoadFloat4x4(&matrix);

	D3D11_MAPPED_SUBRESOURCE data = {};
	context->Map(this->meshBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &data);

	MeshBuffer* meshBuffer = static_cast<MeshBuffer*>(data.pData);
	XMStoreFloat4x4(&(meshBuffer->Matrix), XMMatrixTranspose(mMatrix));

	context->Unmap(this->meshBuffer, 0);

	context->VSSetConstantBuffers(0, 1, &this->meshBuffer);

	UINT offset = 0;

	context->IASetVertexBuffers(0, 1, &vertexBuffer, &vertexStride, &offset);
	context->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R16_UINT, offset);
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	context->DrawIndexed(indexCount, 0, 0);
}

void Mesh::Update(float deltaTime)
{
	UpdateMatrix();
}

void Mesh::SetVertecies(ID3D11Device* device, vector<Vertex> vertices)
{
    vertexCount = vertices.size();
    vertexStride = sizeof(Vertex);

    D3D11_BUFFER_DESC desc = {};
    desc.ByteWidth = vertexCount * vertexStride;
    desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;      
    desc.Usage = D3D11_USAGE_IMMUTABLE;             

    D3D11_SUBRESOURCE_DATA initialData = {};
    initialData.pSysMem = vertices.data();

    device->CreateBuffer(&desc, &initialData, &vertexBuffer);
}

void Mesh::SetIndices(ID3D11Device* device, vector<short> indices)
{
	indexCount = indices.size();

    D3D11_BUFFER_DESC desc = {};
    desc.ByteWidth = indexCount * sizeof(short);
    desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    desc.Usage = D3D11_USAGE_IMMUTABLE;

    D3D11_SUBRESOURCE_DATA initialData = {};
    initialData.pSysMem = indices.data();

    device->CreateBuffer(&desc, &initialData, &indexBuffer);
}

void Mesh::UpdateMatrix()
{
	XMMATRIX translation = XMMatrixTranslation(Position.x, Position.y, Position.z);
	XMMATRIX rotation = XMMatrixRotationRollPitchYaw(Rotation.x, Rotation.y, Rotation.z);
	XMMATRIX scale = XMMatrixScaling(Scale.x, Scale.y, Scale.z);

	XMStoreFloat4x4(&matrix, scale * rotation * translation);
}

void Mesh::InitBuffer(ID3D11Device* device)
{
	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.ByteWidth = sizeof(MeshBuffer);
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	device->CreateBuffer(&bufferDesc, nullptr, &meshBuffer);
}