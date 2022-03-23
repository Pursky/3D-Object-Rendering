Texture2D MainTexture;
sampler MainSampler;

struct PixelInput
{
    float4 position : SV_POSITION;
    float2 uv : TEXCOORD;
};

float4 main(PixelInput INPUT) : SV_TARGET
{
    // Samples the texture and returns the pixel color value.
    return MainTexture.Sample(MainSampler, INPUT.uv);
}