Texture2D MainTexture;
sampler MainSampler;

cbuffer LightBuffer
{
    float3 lightDirection;
    float lightIntensity;
    float4 lightDiffuseColor;
    float4 ambientColor;
};

cbuffer MaterialBuffer
{
    float specularPower;
    float glossy;
};

struct PixelInput
{
    float4 position : SV_POSITION;
    float3 normal : NORMAL;
    float2 uv : TEXCOORD0;
    float3 viewDirection : TEXCOORD1;
};

float4 main(PixelInput INPUT) : SV_TARGET
{
    // Samples the texture.
    float4 textureColor = MainTexture.Sample(MainSampler, INPUT.uv);
    
    // Sets up normal and inverse light direction.
    float3 normal = normalize(INPUT.normal);
    float3 light = normalize(-lightDirection);
    
    // Calculates the diffuse color.
    float4 diffuseColor = lightDiffuseColor * max(dot(normal, light), 0) * lightIntensity;
    
    // Calculates the specular reflection.
    float specular = pow(max(dot(reflect(-light, normal), normalize(INPUT.viewDirection)), 0), specularPower) * glossy;
    float4 specColor = lightDiffuseColor * specular;
    
    // Returns the pixel color value.
    return saturate(textureColor * saturate(ambientColor + diffuseColor) + specColor);
}