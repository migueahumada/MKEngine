#pragma once
#include "Prerequisites.h"
#include <d3d12.h>

class MK_DX12_API GraphicsDevice
{
 public:
  GraphicsDevice() = default;
  ~GraphicsDevice()
  {
    if (m_device)
    {
      m_device->Release();
    }
  }

  ID3D12Device** getDevice()
  {
    return &m_device;
  }

 protected:
  ID3D12Device* m_device = nullptr;
};

