cbuffer cbObject_Info : register(b0) {
	matrix gmtx_World : packoffset(c0);
}

cbuffer cbCamera_Info : register(b1) {
	matrix gmtx_View : packoffset(c0);
	matrix gmtx_Projection : packoffset(c4);
}

struct VS_INPUT {
	float3 position : POSITION;
	float4 color : COLOR;
};

struct VS_OUTPUT {
	float4 position : SV_POSITION;
	float4 color : COLOR;
};

VS_OUTPUT VSDiffused(VS_INPUT input) {
	VS_OUTPUT output;

	output.position = mul(mul(mul(float4(input.position, 1.0f), gmtx_World), gmtx_View), gmtx_Projection);
	output.color = input.color;

	return output;
}

float4 PSDiffused(VS_OUTPUT input) : SV_TARGET{
	return input.color;
}