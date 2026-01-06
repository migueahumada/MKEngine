#pragma once
#include "PrerequisitesDX11.h"
#include "Subsystem.h"

class DX11GraphicsAPI;

class DX11Renderer : public Subsystem<DX11Renderer>
{

  
public:
  MK_DX11_API DX11Renderer() = default;
  MK_DX11_API virtual ~DX11Renderer() = default;

  MK_DX11_API void Render();

protected:
  
  virtual void OnStartUp() override;
  virtual void OnShutDown() override;

  

private:
  
  
  

};

