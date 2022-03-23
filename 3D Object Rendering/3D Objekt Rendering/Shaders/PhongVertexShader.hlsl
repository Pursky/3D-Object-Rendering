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
    float3 normal : NORMAL;
    float2 uv : TEXCOORD;
};

struct VertexOutput
{
    float4 position : SV_POSITION;
    float3 normal : NORMAL;
    float2 uv : TEXCOORD0;
    float3 viewDirection : TEXCOORD1;
};

VertexOutput main(VertexInput INPUT)
{
    VertexOutput OUTPUT;
    
    // Calculates the vertex position into world space.
    float4 worldPosition = mul(float4(INPUT.position, 1.0f), meshMatrix);
    
    // Multiplies the combined camera matrix with the world position.
    OUTPUT.position = mul(worldPosition, camMatrix);
    
    // Translates the normal into world space.
    OUTPUT.normal = normalize(mul(INPUT.normal, (float3x3) meshMatrix));
    
    // Passes uvs to the pixel shader.
    OUTPUT.uv = INPUT.uv;
    
    // Calculates the view direction.
    OUTPUT.viewDirection = camPosition - worldPosition.xyz;
    
    // Returns the vertex output struct.
    return OUTPUT;
}