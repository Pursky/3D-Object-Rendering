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
};

struct VertexOutput
{
    float4 position : SV_POSITION;
    float3 normal : NORMAL;
};

VertexOutput main(VertexInput INPUT)
{
    VertexOutput OUTPUT;
    
    // Calculates the vertex position into world space.
    float4 worldPosition = mul(float4(INPUT.position, 1.0f), meshMatrix);
    
    // Multiplies the combined camera matrix with the world position.
    OUTPUT.position = mul(worldPosition, camMatrix);
    
    // Translates the normal into world space.
    float3 normal =  normalize(mul(INPUT.normal, (float3x3) meshMatrix));
    
    // Relfects the normal around the view direction.
    normal = reflect(-normalize(camPosition - worldPosition.xyz), normal);
    
    // Passes the new normal to the pixel shader.
    OUTPUT.normal = normal;
    
    // Returns the vertex output struct.
    return OUTPUT;
}