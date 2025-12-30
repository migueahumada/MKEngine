#pragma once
#include <d3d12.h>
class mkD3D12CommandQueue
{
public:
  mkD3D12CommandQueue() = default;
  virtual ~mkD3D12CommandQueue()
  {
    if (m_commandQueue)
    {
      m_commandQueue->Release();
      m_commandQueue = nullptr;
    }
  }

  inline ID3D12CommandQueue** getInterface()
  {
    return &m_commandQueue;
  }

protected:

  ID3D12CommandQueue* m_commandQueue = nullptr;
  

};

