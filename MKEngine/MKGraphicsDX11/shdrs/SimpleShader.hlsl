
struct VertexInput
{
  float3 position : POSITION0;
  float3 color : COLOR0;
};

struct PixelInput
{
  float4 position : SV_Position;
  float3 color : COLOR0;
};

PixelInput vertex_main(VertexInput Input)
{
  PixelInput Output = (PixelInput) 0;
  
  Output.position = float4(Input.position, 1);
  Output.color = Input.color;
  
  return Output;

}

float4 pixel_main(PixelInput Input) : SV_Target
{
  float4 color = float4(Input.color, 1.0f);
  
  return color;
}

