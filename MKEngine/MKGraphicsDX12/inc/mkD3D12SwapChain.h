#pragma once

#include <dxgi1_6.h>

class mkD3D12SwapChain
{
public:
  mkD3D12SwapChain() = default;
  virtual ~mkD3D12SwapChain()
  {
    if (m_swapChain)
    {
      m_swapChain->Release();
      m_swapChain = nullptr;
    }
  }

  inline IDXGISwapChain3** getInterface()
  {
    return &m_swapChain;
  }

protected:
  IDXGISwapChain3* m_swapChain = nullptr;
};

