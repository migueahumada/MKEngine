#include "Application.h"
#include <SDL3/SDL_time.h>
#include "DX12GraphicsAPI.h"
#include "DX11GraphicsAPI.h"

Application::Application()
{
  
}

Application::~Application()
{
  SDL_DestroyWindow(m_window);
}

void Application::Run()
{
  Uint64 lastTime = SDL_GetPerformanceCounter();
  Uint64 currentTime = 0;
  Init();

  while (!m_isFinished)
  {
    //Start of frame
    currentTime = SDL_GetPerformanceCounter();
    
    double frameTime = static_cast<double>(currentTime - lastTime);
    float deltaTime = frameTime / SDL_GetPerformanceFrequency();
    lastTime = currentTime;

    //printf("DeltaTime in MS: %f \n", deltaTime * 1e3f );
    //printf("FrameTime in MS: %f\r", frameTime / SDL_GetPerformanceFrequency() * 1e3f);
    

    if (deltaTime < 1.0f/60.0f)
    {
      Uint32 delayMs = (Uint32)(((1.0f / 60.0f) - deltaTime) * 1000.0f);
      SDL_Delay(delayMs);
    }

    Update(deltaTime);
    

    Render();

  }

  Shutdown();

}

void Application::Init()
{
  if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS))
  {

    SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
  }


  m_window = SDL_CreateWindow(m_windowTitle, m_width, m_height, SDL_WINDOW_RESIZABLE);
  if (!m_window)
  {
    printf("Error Creating SDL Window");
  }

  void* handle = SDL_GetPointerProperty(SDL_GetWindowProperties(m_window), SDL_PROP_WINDOW_WIN32_HWND_POINTER, nullptr);



  if (m_appDesc.graphicsBackend == GraphicsBackend::DX12)
  {
    DX12GraphicsAPI::StartUp(handle);
  }else
  {
    DX11GraphicsAPI::StartUp(handle);
  }

  

  //////
  

}

void Application::Update(float deltaTime)
{

}


void Application::Render()
{

}

void Application::Shutdown()
{
  if (m_appDesc.graphicsBackend == GraphicsBackend::DX12)
  {
    DX12GraphicsAPI::ShutDown();
  }else
  {
    DX11GraphicsAPI::ShutDown();
  }

  
}
