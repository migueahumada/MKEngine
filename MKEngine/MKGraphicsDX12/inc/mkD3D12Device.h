#pragma once
#include "Prerequisites.h"
#include <d3d12.h>

class MK_DX12_API mkD3D12Device
{
 public:
  mkD3D12Device() = default;
  virtual ~mkD3D12Device()
  {
    if (m_device)
    {
      m_device->Release();
      m_device = nullptr;      
    }
  }

  inline ID3D12Device* getDevice()
  {
    return m_device;
  }

  inline ID3D12Device** getInterface()
  {
    return &m_device;
  }

 protected:
  ID3D12Device* m_device = nullptr;
};

