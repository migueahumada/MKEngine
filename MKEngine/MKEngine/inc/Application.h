#pragma once
#include <SDL3/SDL.h>
#include "PrerequisitesCore.h"

namespace AudioBackend
{
  enum E {
    kXAudio2,
    kWwise,
    kFmod,
  };
}

namespace GraphicsBackend
{
  enum E {
    DX11,
    DX12,
    OPENGL,
  };
}

struct APP_DESC {

};

class Application
{
 public:
  Application();
  ~Application();

  void Run();

 protected:
  void Init();
  void Update(float deltaTime);
  void Render();
  void Shutdown();

  SDL_Window* m_window = nullptr;
  const char* m_windowTitle = "MK Engine";
  const uint16 m_height = 720;
  const uint16 m_width = 1080;
  bool m_isFinished = false;
  
};

