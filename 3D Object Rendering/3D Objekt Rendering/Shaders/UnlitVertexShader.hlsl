cbuffer MeshBuffer
{
    float4x4 meshMatrix;
};

cbuffer CameraBuffer
{
    float4x4 camMatrix;
    float3 camPosition;
};

struct VertexInput
{
    float3 position : POSITION;
    float2 uv : TEXCOORD;
};

struct VertexOutput
{
    float4 position : SV_POSITION;
    float2 uv : TEXCOORD;
};

VertexOutput main(VertexInput INPUT)
{
    VertexOutput OUTPUT;
	
    // Multiplies the combined camera matrix with the mesh matrix.
    OUTPUT.position = mul(float4(INPUT.position, 1.0f), mul(meshMatrix, camMatrix));
    
    // Passes uvs to the pixel shader.
    OUTPUT.uv = INPUT.uv;
	
    // Returns the vertex output struct.
    return OUTPUT;
}