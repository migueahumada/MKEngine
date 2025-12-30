#pragma once
#include "Prerequisites.h"
#include "Subsystem.h"
#include <d3d12.h>
#include <dxgi1_6.h>
#include "mkD3D12DescriptorHeap.h"

//#include "d3dx12.h"

class mkD3D12DescriptorHeap;

namespace ResourceType {
  enum E {
    RTV,
    SRV,
    DSV,
    UAV
  };
}

class  DX12GraphicsAPI : public Subsystem<DX12GraphicsAPI>
{

public:
  MK_DX12_API explicit DX12GraphicsAPI(void* hWnd);
  MK_DX12_API virtual ~DX12GraphicsAPI() = default;

  UPtr<mkD3D12DescriptorHeap> CreateDescriptorHeap(UINT numDescriptors = 1,
                                                   D3D12_DESCRIPTOR_HEAP_TYPE type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV,
                                                   D3D12_DESCRIPTOR_HEAP_FLAGS flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE);

protected:
  void OnStartUp() override;
  void OnShutDown() override;
  
  void* m_hWnd {nullptr};
  ID3D12Device6* m_device {nullptr};
  ID3D12CommandQueue* m_commandQueue {nullptr};
  IDXGISwapChain3* m_swapChain {nullptr};
  ID3D12CommandAllocator* m_commandAllocator {nullptr};
  CD3DX12_VIEWPORT m_viewport;

  UPtr<mkD3D12DescriptorHeap> m_frontBackBuffersHeap;
  UPtr<mkD3D12DescriptorHeap> m_srvHeap;
 
  

private:
  void SetDebugControllerFlags(UINT& flags);
  void CreateDevice(UINT flags);
  void CreateCommandQueue(UINT flags = D3D12_COMMAND_QUEUE_FLAG_NONE);
  void CreateSwapChain(UINT flags);
  void CreateFrontBackBuffers();
  void CreateCommandAllocator(UINT flags);
  void CreateViewport(UINT flags);
  
  
  
};

 DX12GraphicsAPI& g_dx12GraphicsAPI();