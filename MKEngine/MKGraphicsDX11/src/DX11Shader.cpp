#include "DX11Shader.h"
#include <fstream>
#include <assert.h>
#include <d3dcompiler.h>

using std::fstream;

void DX11Shader::Compile(const Path& filePath,
                               const String& entryFunction,
                               const String& shaderModel)
{
  //Start the read pointer at the end (ate)
  fstream file(filePath, std::ios::in | std::ios::ate);
	assert(file && "File on VertexShader coudln't be loaded!");

  //Filesize in bytes
  std::streampos fileSize = file.tellg();
  file.seekg(std::ios::beg);

  //Create a vector, resize it and fill it with the data;
  std::vector<char> shaderCode;
  shaderCode.resize(static_cast<size_t>(fileSize));
  file.read(shaderCode.data(), shaderCode.size());

  UINT flags = D3DCOMPILE_ENABLE_STRICTNESS;

#ifdef _DEBUG
  flags |= D3DCOMPILE_DEBUG;
#endif // _DEBUG
  
  HRESULT hr;

  ID3DBlob* pErrorBlob = nullptr;

  hr = D3DCompile(shaderCode.data(), 
                  shaderCode.size(), 
                  nullptr, 
                  nullptr, 
                  nullptr,
                  entryFunction.c_str(),
                  shaderModel.c_str(),
                  flags,
                  0,
                  &m_pBlob,
                  &pErrorBlob);
  if (FAILED(hr))
  {
    MessageBoxA(nullptr, (LPCSTR)pErrorBlob->GetBufferPointer(),"Error", MB_OK);
  }
  assert(m_pBlob && "Couldn't generate blob");

  file.close();
}

DX11VertexShader::DX11VertexShader()
{
  
}
