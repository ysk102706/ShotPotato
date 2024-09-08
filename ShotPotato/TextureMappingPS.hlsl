struct ps_input
{
    float4 position : POSITION;
    float2 texCoord : TEXCOORD;
};

Texture2D image;
SamplerState samplerState;

float4 PS(ps_input input) : SV_TARGET
{
    float4 color = image.Sample(samplerState, input.texCoord);
    
    return color;
}