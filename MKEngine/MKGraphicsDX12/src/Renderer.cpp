#include "Renderer.h"
#include "DX12GraphicsAPI.h"

void Renderer::OnStartUp()
{
  
}

void Renderer::OnShutDown()
{

}


void Renderer::SetDebugControllerFlags(UINT& flags)
{
  HRESULT hr;
  ID3D12Debug* debugController;


  hr = D3D12GetDebugInterface(IID_PPV_ARGS(&debugController));
  if (SUCCEEDED(hr))
  {
    debugController->EnableDebugLayer();

    debugController->Release();

    flags |= DXGI_CREATE_FACTORY_DEBUG;
  }
}