#pragma once
#include "Subsystem.h"
#include <d3d12.h>
#include <dxgi1_6.h>



class Renderer : public Subsystem<Renderer>
{
public:

  Renderer() = default;
  virtual ~Renderer() = default;

  
  void OnStartUp() override;
  void OnShutDown() override;

  
  void SetDebugControllerFlags(UINT& flags);

protected:
  
  
};

