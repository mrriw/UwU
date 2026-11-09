struct Input
{
};

struct Output
{
	float4 Color : SV_Target0;
};

Output main(Input input)
{
	Output output;
	output.Color = float4(0.6f, 0.1f, 0.4f, 1.0f);

	return output;
}
