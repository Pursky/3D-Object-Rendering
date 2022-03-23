#include "Sphere.h"
#include <vector>

Sphere::Sphere(ID3D11Device* device, Material* mat, int resolution, bool inverse, XMFLOAT3 position, XMFLOAT3 rotation, XMFLOAT3 scale)
{
    this->resolution = resolution;
    this->inverse = inverse;

    if (scale.x == 0 && scale.y == 0 && scale.z == 0) scale = { 1.0f, 1.0f, 1.0f };

    Position =  position;
    Rotation =  rotation;
    Scale =     { 1.0f, 1.0f, 1.0f };

    Mat = mat;

    SetVertecies(device);
    SetIndices(device);

    XMStoreFloat4x4(&matrix, XMMatrixIdentity());

    InitBuffer(device);
}

void Sphere::Update(float deltaTime)
{
    UpdateMatrix();
}

void Sphere::SetVertecies(ID3D11Device* device)
{
    int xSize = (resolution * 2) - 1;
    int ySize = resolution;

    std::vector<Vertex> vertices;
    float triMult = 180.0f / ((float)resolution - 1);

    float xF = 0;
    float yF = 0;
    float zF = 0;

    float uvX = 0;
    float uvY = 0;
        
    for (int y = 0; y < ySize; y++)
    {
        for (int x = 0; x < xSize; x++)
        {
            yF =  DegCos(triMult * (float)y) * 0.5f;
            
            xF = -DegSin(triMult * (float)x) * 0.5f * DegSin(triMult * (float)y);
            zF =  DegCos(triMult * (float)x) * 0.5f * DegSin(triMult * (float)y);

            uvX = (float)x / ((float)xSize - 1.0f);
            uvY = (float)y / ((float)ySize - 1.0f);

            vertices.push_back({ xF,  yF,  zF, /*Normals*/ xF, yF, zF, /*UVs*/ uvX, uvY });
        }
    }

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

void Sphere::SetIndices(ID3D11Device* device)
{
    int xSize = (resolution * 2) - 1;
    int ySize = resolution - 1;

    std::vector<short> indices;

    int topLeft = 0;
    int topRight = 0;
    int bottomLeft = 0;
    int bottomRight = 0;

    for (int y = 0; y < ySize; y++)
    {
        for (int x = 0; x < xSize; x++)
        {
            topLeft = y * xSize + x;
            topRight = topLeft + 1;
            bottomLeft = topLeft + xSize;
            bottomRight = topRight + xSize;

            if (inverse) 
            {
                indices.push_back(bottomLeft); indices.push_back(topRight); indices.push_back(topLeft);
                indices.push_back(bottomLeft); indices.push_back(bottomRight); indices.push_back(topRight);
            }
            else 
            {
                indices.push_back(topLeft); indices.push_back(topRight); indices.push_back(bottomLeft);
                indices.push_back(topRight); indices.push_back(bottomRight); indices.push_back(bottomLeft);
            }
        }
    }

    indexCount = indices.size();

    D3D11_BUFFER_DESC desc = {};
    desc.ByteWidth = indexCount * sizeof(short);
    desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    desc.Usage = D3D11_USAGE_IMMUTABLE;

    D3D11_SUBRESOURCE_DATA initialData = {};
    initialData.pSysMem = indices.data();

    device->CreateBuffer(&desc, &initialData, &indexBuffer);
}