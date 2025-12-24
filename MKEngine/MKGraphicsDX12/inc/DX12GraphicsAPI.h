#pragma once
#include "Prerequisites.h"
#include "Subsystem.h"
#include <d3d12.h>
#include <dxgi1_6.h>
//#include "d3dx12.h"


class MK_DX12_API DX12GraphicsAPI : public Subsystem<DX12GraphicsAPI>
{

public:
  explicit DX12GraphicsAPI(void* hWnd);
  virtual ~DX12GraphicsAPI() = default;

protected:
  void OnStartUp() override;
  void OnShutDown() override;
  
  void* m_hWnd {nullptr};
  ID3D12Device6* m_device{ nullptr };
  ID3D12CommandQueue* m_commandQueue {nullptr};
  IDXGISwapChain3* m_swapChain{nullptr};
  ID3D12Resource* m_renderTargets[2];
 
private:
  void SetDebugControllerFlags(UINT& flags);
  void CreateDevice(UINT flags);
  void CreateCommandQueue(UINT flags = D3D12_COMMAND_QUEUE_FLAG_NONE);
  void CreateSwapChain(UINT flags);
  
};

 DX12GraphicsAPI& g_dx12GraphicsAPI()
{
  return DX12GraphicsAPI::GetInstance();
}