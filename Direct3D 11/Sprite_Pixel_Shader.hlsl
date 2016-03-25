Texture2D tex;
SamplerState ss;

struct Pixel_In
{
	float4 position : SV_POSITION;
	float2 texcoord : TEXCOORD0;
};

float4 main(Pixel_In p_in) : SV_TARGET
{
	return tex.Sample(ss, p_in.texcoord);
}