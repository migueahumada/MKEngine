#include "DX11Renderer.h"
#include "DX11GraphicsAPI.h"

void DX11Renderer::OnStartUp()
{
  Vector<D3D11_INPUT_ELEMENT_DESC> inputDesc = 
  {
    {"COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA,0},
    {"POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA,0 }
  };

  
  

  
}

void DX11Renderer::OnShutDown()
{

}

void Render()
{
 
}
