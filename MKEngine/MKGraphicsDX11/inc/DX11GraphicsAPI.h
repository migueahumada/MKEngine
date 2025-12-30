#pragma once
#include "PrerequisitesDX11.h"
#include "Subsystem.h"
#include <d3d11_2.h>
#include <dxgi.h>

class DX11GraphicsAPI : public Subsystem<DX11GraphicsAPI> 
{
public:

  MK_DX11_API explicit DX11GraphicsAPI(void* hwnd);
  MK_DX11_API virtual ~DX11GraphicsAPI() = default;

protected:
  void OnStartUp() override;
  void OnShutDown() override;



private:

  void CreateDevice();
  void CreateContext();
  void CreateSwapChain();
  void CreateViewport();

  void* m_hwnd {nullptr};
  ID3D11Device* m_device {nullptr};
  ID3D11DeviceContext* m_deviceContext {nullptr};
};

DX11GraphicsAPI& g_dx11GraphicsAPI();

