#pragma once
#include "PrerequisitesDX11.h"
#include <d3d11_2.h>
#include <fstream>
class DX11Shader
{
  
public:
  DX11Shader() = default;
  virtual ~DX11Shader()
  {

    SAFE_RELEASE(m_pBlob);

  }

  inline ID3DBlob* getBlob()
  {
    return m_pBlob;
  }


  void Compile(const Path& filePath, 
                       const String& entryFunction,
                       const String& shaderModel);

protected:

  ID3DBlob* m_pBlob {nullptr};
};


class DX11VertexShader : public DX11Shader
{

public:
  DX11VertexShader();
  virtual ~DX11VertexShader()
  {
    SAFE_RELEASE(m_pVertexShader);
  }

protected:
  ID3D11VertexShader* m_pVertexShader {nullptr};

};

class DX11PixelShader : public DX11Shader
{
  
public:
  DX11PixelShader() = default;
  virtual ~DX11PixelShader()
  {
    SAFE_RELEASE(m_pPixelShader);
  }

private:
  ID3D11PixelShader* m_pPixelShader {nullptr};
  
};


