Texture2D MainTexture;
sampler MainSampler;

cbuffer LightBuffer
{
    float3 lightDirection;
    float lightIntensity;
    float4 lightDiffuseColor;
    float4 ambientColor;
    float rotation;
};

struct PixelInput
{
    float4 position : SV_POSITION;
    float3 normal : NORMAL;
};

float4 main(PixelInput INPUT) : SV_TARGET
{
    // Renormalizes the normal.
    float3 normal = normalize(INPUT.normal);
    
    // Translates the normal vector into uv coordinates on a uv sphere map. (0.159155 = 1/(2*PI), 0.318309 = 1/PI)
    float x = -atan2(normal.x, normal.z) * 0.159155f + rotation * 0.15915f;
    float y = -asin(normal.y) * 0.318309f + 0.5f;
    
    // Returns the pixel color value.
    return MainTexture.Sample(MainSampler, float2(x, y));
}