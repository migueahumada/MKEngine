#pragma once
#include "PrerequisitesDX11.h"
#include "Subsystem.h"
#include <d3d11_2.h>
#include <dxgi.h>

class DX11PixelShader;
class DX11VertexShader;
class DX11Shader;

class DX11GraphicsAPI : public Subsystem<DX11GraphicsAPI> 
{
  friend class DX11Renderer;
public:

  MK_DX11_API explicit DX11GraphicsAPI(void* hwnd);
  MK_DX11_API virtual ~DX11GraphicsAPI() = default;

 UPtr<DX11PixelShader>CreatePixelShader(const Path& filePath,
                                         const String& entryFunction);
  

protected:
  void OnStartUp() override;
  void OnShutDown() override;



private:

  void CreateDeviceAndImmmediateContext(IDXGIAdapter* pAdapter);
  void CreateSwapChain(IDXGIAdapter* pAdapter);
  void CreateBackBuffer(int widht, int height);
  void CreateViewport();

  Vector<IDXGIAdapter1*> getAdapters();

private:
  void* m_hwnd {nullptr};
  ID3D11Device* m_pDevice {nullptr};
  ID3D11DeviceContext* m_pDeviceContext {nullptr};
  IDXGISwapChain1* m_pSwapChain {nullptr};
  ID3D11RenderTargetView* m_pBackBufferRTV {nullptr};
  ID3D11DepthStencilView* m_pBackBufferDSV {nullptr};

  const uint16 m_width {1280};
  const uint16 m_height {720};

};

DX11GraphicsAPI& g_dx11GraphicsAPI();

