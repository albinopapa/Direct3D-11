cbuffer Transforms
{
	matrix world;
	matrix view;
	matrix projection;
}

struct V_In
{
	float3 position :POSITION;
	float2 texcoord :TEXCOORD0;
};

struct V_Out
{
	float4 position :SV_POSITION;
	float2 texcoord :TEXCOORD0;
};

V_Out main( V_In v_in )
{
	float4 position = float4( v_in.position, 1.0f );

	position = mul( position, world );
	position = mul( position, view );
	position = mul( position, projection );

	V_Out v_out;
	v_out.position = position;
	v_out.texcoord = v_in.texcoord;

	return v_out;
}