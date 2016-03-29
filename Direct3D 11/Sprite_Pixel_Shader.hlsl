Texture2D tex;
SamplerState ss;

struct Pixel_In
{
	float4 position : SV_POSITION;
	float2 texcoord : TEXCOORD0;
};

float4 main(Pixel_In p_in) : SV_TARGET
{
	float cut_off_depth = 0.999f;
	float alpha = (p_in.position.z - cut_off_depth) / (1.0f - cut_off_depth);
	alpha = 1.0f - saturate(alpha);
	
	float4 color = tex.Sample(ss, p_in.texcoord);
	color = float4(color.r * alpha, color.g * alpha, color.b * alpha, 1.0f);
	return color;
}