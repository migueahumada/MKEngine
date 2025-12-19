#pragma once
#include <SDL3\SDL.h>


class Application
{
 public:
  Application() = default;
  ~Application() = default;

  void Update(float deltaTime);
  void FixedUpdate();
  void Render();

};

