#include "DX11GraphicsAPI.h"
#include "DX11Shader.h"

DX11GraphicsAPI::DX11GraphicsAPI(void* hwnd) : m_hwnd(hwnd)
{
  
 

}

UPtr<DX11PixelShader> DX11GraphicsAPI::CreatePixelShader(const Path& filePath, const String& entryFunction)
{
  
  UPtr<DX11PixelShader> pPixelShader = make_unique<DX11PixelShader>();
  pPixelShader->Compile(filePath, entryFunction, "ps_5_0");
  
  assert(pPixelShader->getBlob() && "Blob wasn't create");


  return pPixelShader;
}


void DX11GraphicsAPI::OnStartUp()
{
  HRESULT hr;

  IDXGIAdapter* defaultAdapter = getAdapters()[0];

  CreateDeviceAndImmmediateContext(defaultAdapter);
  
  CreateSwapChain(defaultAdapter);
  
  CreateBackBuffer(m_width, m_height);
  
  CreateViewport();

  
  CreatePixelShader(L"D:/Coding/C++/MKEngine/MKEngine/MKGraphicsDX11/shdrs/SimpleShader.hlsl","pixel_main");
  
  //CLEANUP
  SAFE_RELEASE(defaultAdapter);

}

void DX11GraphicsAPI::OnShutDown()
{
}

void DX11GraphicsAPI::CreateDeviceAndImmmediateContext(IDXGIAdapter* pAdapter)
{
  HRESULT hr;

 

  Vector<D3D_FEATURE_LEVEL> featureLevels = { D3D_FEATURE_LEVEL_11_0,
                                              D3D_FEATURE_LEVEL_11_1 };

  D3D_FEATURE_LEVEL selectedFeatureLevel;

  UINT deviceFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

#ifdef _DEBUG
  deviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif // _DEBUG


  hr = D3D11CreateDevice(pAdapter,
                         D3D_DRIVER_TYPE_UNKNOWN,
                         nullptr,
                         deviceFlags,
                         featureLevels.data(),
                         (UINT)featureLevels.size(),
                         D3D11_SDK_VERSION,
                         &m_pDevice,
                         &selectedFeatureLevel,
                         &m_pDeviceContext);

  assert(m_pDevice && "device couldnt be created");
  assert(m_pDeviceContext && "device couldnt be created");
}


void DX11GraphicsAPI::CreateSwapChain(IDXGIAdapter* pAdapter)
{

  HRESULT hr;

  RECT rect;

  HWND hwnd = static_cast<HWND>(m_hwnd);
  GetClientRect(hwnd, &rect);

  DXGI_SWAP_CHAIN_DESC1 scDesc{ 0 };
  scDesc.Width = rect.right - rect.left;
  scDesc.Height = rect.bottom - rect.top;
  scDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
  scDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
  scDesc.Scaling = DXGI_SCALING_NONE;
  scDesc.Stereo = false;
  scDesc.SampleDesc.Count = 1;
  scDesc.SampleDesc.Quality = 0;
  scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
  scDesc.BufferCount = 2;

  IDXGIFactory2* pFactory2 = nullptr;
  hr = pAdapter->GetParent(__uuidof(IDXGIFactory2),(void**) &pFactory2);

  hr = pFactory2->CreateSwapChainForHwnd(m_pDevice,hwnd,&scDesc, nullptr,nullptr, &m_pSwapChain);
  assert(m_pSwapChain && "Swapchain Couldn't be created");

  IDXGIDevice1* pDXGIDevice1 = nullptr;
  m_pDevice->QueryInterface(__uuidof(IDXGIDevice1), (void**)&pDXGIDevice1);

  pDXGIDevice1->SetMaximumFrameLatency(3);

  SAFE_RELEASE(pFactory2);
  SAFE_RELEASE(pDXGIDevice1);
  
}

void DX11GraphicsAPI::CreateBackBuffer(int width, int height)
{
  HRESULT hr;

  //RTV
  ID3D11Texture2D* pBackBuffer = nullptr;
  hr = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBackBuffer);
  assert(pBackBuffer && "Back buffer texture couldn't be created.");

  hr = m_pDevice->CreateRenderTargetView(pBackBuffer,nullptr, &m_pBackBufferRTV);
  assert(m_pBackBufferRTV && "Couldn't Create RTV for back buffer");

  SAFE_RELEASE(pBackBuffer);

  //Depth Stencil
  ID3D11Texture2D* pDepthStencil = nullptr;

  D3D11_TEXTURE2D_DESC texDesc {0};
  
  texDesc.ArraySize = 1;
  texDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
  texDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
  texDesc.Usage = D3D11_USAGE_DEFAULT;
  texDesc.MipLevels = 1;
  texDesc.CPUAccessFlags = 0;
  texDesc.Width = width;
  texDesc.Height = height;
  texDesc.MiscFlags = 0;
  texDesc.SampleDesc.Count = 1;
  texDesc.SampleDesc.Quality = 0;

  hr = m_pDevice->CreateTexture2D(&texDesc,nullptr,&pDepthStencil);

  assert(pDepthStencil && "Couldn't create depthstecnil texture");

  D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc = CD3D11_DEPTH_STENCIL_VIEW_DESC();
  dsvDesc.Flags = 0;
  dsvDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
  dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;

  hr = m_pDevice->CreateDepthStencilView(pDepthStencil,&dsvDesc,&m_pBackBufferDSV);
  assert(m_pBackBufferDSV && "Couldn't create DSV on the back buffer.");


  SAFE_RELEASE(pDepthStencil);
  

}

void DX11GraphicsAPI::CreateViewport()
{
  D3D11_VIEWPORT viewport;
  viewport.Width = static_cast<float>(m_width);
  viewport.Height = static_cast<float>(m_height);
  viewport.MinDepth = 0.0f;
  viewport.MaxDepth = 1.0f;
  viewport.TopLeftX = 0;
  viewport.TopLeftY = 0;

  m_pDeviceContext->RSSetViewports(1, &viewport);


}

Vector<IDXGIAdapter1*> DX11GraphicsAPI::getAdapters()
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

  return vAdapters;
}

DX11GraphicsAPI& g_dx11GraphicsAPI()
{
  return DX11GraphicsAPI::GetInstance();
}
