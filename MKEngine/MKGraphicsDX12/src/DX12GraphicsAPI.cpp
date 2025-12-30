#include "DX12GraphicsAPI.h"
#include "mkD3D12DescriptorHeap.h"

DX12GraphicsAPI::DX12GraphicsAPI(void* hWnd) : m_hWnd(hWnd)
{
  
}

void DX12GraphicsAPI::OnStartUp()
{

  UINT dxgiFactoryFlags = 0;

#if defined(_DEBUG)
  {
    SetDebugControllerFlags(dxgiFactoryFlags);
  }
#endif // defined(_DEBUG)

  CreateDevice(dxgiFactoryFlags);
  CreateCommandQueue();
  CreateSwapChain(dxgiFactoryFlags);
  CreateFrontBackBuffers();
  CreateCommandAllocator(0);
  CreateViewport(0);
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
  swapChainDesc.BufferCount = SWAPCHAIN_SIZE;
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

void DX12GraphicsAPI::CreateFrontBackBuffers()
{
  m_frontBackBuffersHeap = CreateDescriptorHeap(SWAPCHAIN_SIZE,
    D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
  assert(m_frontBackBuffersHeap && "RTVHeap couldn't be created");

  m_srvHeap = CreateDescriptorHeap(1U,
    D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV,
    D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE);
  assert(m_srvHeap && "SRVHeap couldn't be created");

  CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(m_frontBackBuffersHeap->getInterfacePtr()->GetCPUDescriptorHandleForHeapStart());

  m_frontBackBuffersHeap->setHandle(rtvHandle);

  //Create BACK AND FRONT BUFFERS
  for (UINT i = 0; i < m_frontBackBuffersHeap->getResources().size(); ++i)
  {
    ID3D12Resource* pResource = m_frontBackBuffersHeap->getResources().at(i);

    m_swapChain->GetBuffer(0, IID_PPV_ARGS(&pResource));
    m_device->CreateRenderTargetView(pResource,
      nullptr,
      m_frontBackBuffersHeap->getHandle());

    m_frontBackBuffersHeap->getResources().at(i) = pResource;

    m_frontBackBuffersHeap->getHandle().Offset(1,
      m_frontBackBuffersHeap->getDescSize());

  }
}

void DX12GraphicsAPI::CreateCommandAllocator(UINT flags)
{
  HRESULT hr;

  hr = m_device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&m_commandAllocator));
  if (FAILED(hr))
  {
    MessageBoxA(nullptr, "Couldn't Create Command Allocator", MB_OK, MB_ICONERROR);
    return;
  }
}

void DX12GraphicsAPI::CreateViewport(UINT flags)
{
  RECT rect;
  GetClientRect(reinterpret_cast<HWND>(m_hWnd), &rect);

  m_viewport = CD3DX12_VIEWPORT(0.0f,
                                0.0f,
                                static_cast<float>(rect.right - rect.left),
                                static_cast<float>(rect.bottom - rect.top));
}



UPtr<mkD3D12DescriptorHeap> DX12GraphicsAPI::CreateDescriptorHeap(UINT numDescriptors,
                                                                  D3D12_DESCRIPTOR_HEAP_TYPE type,
                                                                  D3D12_DESCRIPTOR_HEAP_FLAGS flags)
{
  HRESULT hr;

  D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc = {};
  rtvHeapDesc.NumDescriptors = numDescriptors;
  rtvHeapDesc.Type = type;
  rtvHeapDesc.Flags = flags;

  auto pDescriptorHeap = make_unique<mkD3D12DescriptorHeap>();

  

  hr = m_device->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(pDescriptorHeap->getInterface()));

  if (FAILED(hr))
  {
    return nullptr;
  }

  pDescriptorHeap->getResources().resize((size_t)numDescriptors);
  
  pDescriptorHeap->setDescSize(m_device->GetDescriptorHandleIncrementSize(type));

  return pDescriptorHeap;
}

DX12GraphicsAPI& g_dx12GraphicsAPI()
{
  return DX12GraphicsAPI::GetInstance();
}