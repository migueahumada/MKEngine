#pragma once
#include "PrerequisitesUtils.h"
#include <cassert>

/**
* Simple Singleton template class
*/

class MK_UTILS_API Singleton {

 public:

  static void StartUp()
  {
    assert(!IsStarted() && "Singleton was already started");

    Instance() = new Singleton;

    IsStarted() = true;
  }

  static void Shutdown()
  {
    assert(IsStarted() && "Singleton was not started");

    delete Instance();
    Instance() = nullptr;

    IsStarted() = false;

  }

  static Singleton& GetInstance()
  {
    return *Instance();
  }

  int getNum()
  {
    return m_num;
  }

  int getBool()
  {
    return asdf;
  }

 protected:
  
  Singleton() = default;
  virtual ~Singleton() = default;

  Singleton(const Singleton&) = delete; //NO copy construct
  Singleton(Singleton&&) = delete; //NO move construct

  Singleton& operator=(const Singleton&) = delete; //NO copy construct
  Singleton& operator=(Singleton&&) = delete; //NO move construct

  static Singleton*& Instance()
  {
    static Singleton* inst = nullptr;
    return inst;
  }

  static bool& IsStarted()
  {
    static bool isStarted = false;
    return isStarted;
  }

  int m_num = 34;
  bool asdf = false;

  
};

Singleton& g_Singleton()
{
  return Singleton::GetInstance();
}