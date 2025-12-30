#include "DX11GraphicsAPI.h"

DX11GraphicsAPI::DX11GraphicsAPI(void* hwnd) : m_hwnd(hwnd)
{
  
 

}


void DX11GraphicsAPI::OnStartUp()
{
  
  



  HRESULT hr;

  Vector<IDXGIAdapter1*> vAdapters;
  IDXGIAdapter1* pAdapter1 = nullptr;
  IDXGIFactory1* pFactory1 = nullptr;

  hr = CreateDXGIFactory1(IID_PPV_ARGS(&pFactory1));
  
  assert(pFactory1 && "factory couldnt be created");

  for (UINT i = 0;
    pFactory1->EnumAdapters1(i, &pAdapter1) != DXGI_ERROR_NOT_FOUND;
    ++i)
  {
    DXGI_ADAPTER_DESC1 desc;
    pAdapter1->GetDesc1(&desc);
    vAdapters.push_back(pAdapter1);
  }

  SAFE_RELEASE(pAdapter1);
  SAFE_RELEASE(pFactory1);

  Vector<D3D_FEATURE_LEVEL> featureLevels = {D3D_FEATURE_LEVEL_11_0,
                                       D3D_FEATURE_LEVEL_11_1};

  D3D_FEATURE_LEVEL selectedFeatureLevel;

  UINT deviceFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

#ifdef _DEBUG
  deviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif // _DEBUG


  hr = D3D11CreateDevice(vAdapters[0],
                         D3D_DRIVER_TYPE_UNKNOWN,
                         nullptr,
                         deviceFlags,
                         featureLevels.data(),
                         (UINT)featureLevels.size(),
                         D3D11_SDK_VERSION,
                         &m_device,
                         &selectedFeatureLevel,
                         &m_deviceContext);

  assert(m_device && "device couldnt be created");
  assert(m_deviceContext && "device couldnt be created");

  DXGI_SWAP_CHAIN_DESC1 scDesc{0};
  //AQUIIIIIIII
  

}

void DX11GraphicsAPI::OnShutDown()
{
}

void DX11GraphicsAPI::CreateDevice()
{

}

void DX11GraphicsAPI::CreateContext()
{
}

void DX11GraphicsAPI::CreateSwapChain()
{
}

void DX11GraphicsAPI::CreateViewport()
{
}

DX11GraphicsAPI& g_dx11GraphicsAPI()
{
  return DX11GraphicsAPI::GetInstance();
}
