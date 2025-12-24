#include "DX12GraphicsAPI.h"

DX12GraphicsAPI::DX12GraphicsAPI(void* hWnd) : m_hWnd(hWnd)
{
  
}

void DX12GraphicsAPI::OnStartUp()
{
  HRESULT hr;

  UINT dxgiFactoryFlags = 0;

#if defined(_DEBUG)
  {
    SetDebugControllerFlags(dxgiFactoryFlags);
  }
#endif // defined(_DEBUG)
  
  CreateDevice(dxgiFactoryFlags);

  CreateCommandQueue();

  CreateSwapChain(dxgiFactoryFlags);
  
  
}

void DX12GraphicsAPI::OnShutDown()
{
  m_commandQueue->Release();
  m_device->Release();
}

void DX12GraphicsAPI::SetDebugControllerFlags(UINT& flags)
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

void DX12GraphicsAPI::CreateDevice(UINT flags)
{
  HRESULT hr;
  IDXGIFactory6* pFactory6 = nullptr;
  IDXGIFactory2* pFactory2 = nullptr;

  hr = CreateDXGIFactory2(flags, IID_PPV_ARGS(&pFactory2));

  pFactory2->QueryInterface(IID_PPV_ARGS(&pFactory6));

  if (FAILED(hr))
  {
    MessageBoxA(nullptr, "Couldn't Create DXGIFactory4", MB_OK, MB_ICONERROR);
    return;
  }

  IDXGIAdapter2* pHardwareAdapter = nullptr;

  for (UINT adapterIndex = 0;
    SUCCEEDED(pFactory6->EnumAdapterByGpuPreference(adapterIndex,
      DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE,
      IID_PPV_ARGS(&pHardwareAdapter)));
    ++adapterIndex)
  {

    DXGI_ADAPTER_DESC1 desc;
    pHardwareAdapter->GetDesc1(&desc);

    if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
    {
      pHardwareAdapter->Release();
      continue;
    }

    hr = D3D12CreateDevice(pHardwareAdapter, D3D_FEATURE_LEVEL_12_0, IID_PPV_ARGS(&m_device));
    if (SUCCEEDED(hr))
    {
      pHardwareAdapter->Release();
      pFactory2->Release();
      pFactory6->Release();
      break;
    }
  }

}

void DX12GraphicsAPI::CreateCommandQueue(UINT flags)
{
  HRESULT hr;
  D3D12_COMMAND_QUEUE_DESC queueDesc = {};
  queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
  queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;

  hr = m_device->CreateCommandQueue(&queueDesc,IID_PPV_ARGS(&m_commandQueue));
  if (FAILED(hr))
  {
    MessageBoxA(nullptr, "Couldn't Create CommandQueue", MB_OK, MB_ICONERROR);
    return;
  }
}

void DX12GraphicsAPI::CreateSwapChain(UINT flags)
{
  HRESULT hr;

  HWND hWnd = reinterpret_cast<HWND>(m_hWnd);

  RECT rect;
  GetClientRect(hWnd, &rect);
  
  DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
  swapChainDesc.BufferCount = 2;
  swapChainDesc.Width = rect.right - rect.left;
  swapChainDesc.Height = rect.bottom - rect.top;
  swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
  swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
  swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
  swapChainDesc.SampleDesc.Count = 1;

  IDXGIFactory4* pFactory4 = nullptr;

  hr = CreateDXGIFactory2(flags, IID_PPV_ARGS(&pFactory4));

  hr = pFactory4->CreateSwapChainForHwnd(m_commandQueue, 
                                         hWnd,
                                         &swapChainDesc,
                                         nullptr,
                                         nullptr,
                                         reinterpret_cast<IDXGISwapChain1**>(&m_swapChain));

  pFactory4->MakeWindowAssociation(hWnd, DXGI_MWA_NO_ALT_ENTER);

}
