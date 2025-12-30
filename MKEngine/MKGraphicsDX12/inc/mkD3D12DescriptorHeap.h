#pragma once

#include "Prerequisites.h"
#include <d3d12.h>
#include <d3dx12.h>
#include <vector>



class mkD3D12DescriptorHeap
{
public:
   mkD3D12DescriptorHeap() = default;
   virtual ~mkD3D12DescriptorHeap()
  {
    for (size_t i = 0; i < m_resources.size(); ++i)
    {
      if (m_resources[i])
      {
        m_resources[i]->Release();
        m_resources[i] = nullptr;
      }
    }
  }

   inline const UINT getDescSize() const
  {
    return m_size;
  }

   inline void setDescSize(UINT newSize) 
  {
    m_size = newSize;
  }

  /**
  * 
  */
  inline ID3D12DescriptorHeap* getInterfacePtr()
  {
    return m_descriptorHeap;
  }

  inline ID3D12DescriptorHeap** getInterface()
  {
    return &m_descriptorHeap;
  }

  inline Vector<ID3D12Resource*>& getResources()
  {
    return m_resources;
  }

  inline CD3DX12_CPU_DESCRIPTOR_HANDLE getHandle()
  {
    return m_descriptorHandle;
  }

  inline void setHandle(CD3DX12_CPU_DESCRIPTOR_HANDLE newHandle)
  {
    m_descriptorHandle = newHandle;
  }

protected:
  ID3D12DescriptorHeap* m_descriptorHeap = nullptr;
  Vector<ID3D12Resource*> m_resources;
  UINT m_size = 0;
  CD3DX12_CPU_DESCRIPTOR_HANDLE m_descriptorHandle;

};


