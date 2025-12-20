#pragma once

#include "Singleton.h"

class MK_UTILS_API DummyAPI : public Singleton<DummyAPI>
{
public:
  DummyAPI() {}

  virtual ~DummyAPI() {}

  virtual void OnStartup() override
  {
    
  }
  virtual void OnShutdown() override
  {
    
  }



private:

};
