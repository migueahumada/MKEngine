#pragma once
#include "PrerequisitesUtils.h"
#include <cassert>
#include <utility>

/**
* Simple Singleton template class
*/
/*
template<class T>
class Singleton {

 public:

  template <typename... Args>
  static void StartUp(Args&& ... args)
  {
    assert(!IsStarted() && "Singleton was already started");

    Instance() = new T(std::forward<Args>(args)...);
    IsStarted() = true;

    static_cast<Singleton*>(Instance())->OnStartup();


  }

  virtual void OnStartup() = 0;
  virtual void OnShutdown() = 0;

  static void Shutdown()
  {
    assert(IsStarted() && "Singleton was not started");

    
    static_cast<Singleton*>(Instance())->OnShutdown();
    delete Instance();
    IsStarted() = false;
  }

  static T& GetInstance()
  {
    return *Instance();
  }

 protected:
  
  Singleton() = default;
  virtual ~Singleton() = default;

  Singleton(const Singleton&) = delete; //NO copy construct
  Singleton(Singleton&&) = delete; //NO move construct

  Singleton& operator=(const Singleton&) = delete; //NO copy construct
  Singleton& operator=(Singleton&&) = delete; //NO move construct

  static bool& IsStarted()
  {
    static bool isStarted = false;
    return isStarted;
  }

  static T*& Instance()
  {
    static T* inst = nullptr;
    return inst;
  }

  int m_num = 34;
  bool asdf = false;

  
};*/

/*
* El problema del singleton es que hace ahuevo 
* solo existe una instancia de esa clase.
*/

template <class A>
class System 
{
 public:

  template <typename... Args>
  static void StartUp(Args&&... args)
  {
    if (true)
    {

    }
    Instance() = new A(std::forward<Args>(args)...);
    
  }

  static void ShutDown()
  {
    delete Instance();
    Instance() = nullptr;
  }

  static A& GetInstace()
  {
    return *Instance();
  }
  

 protected:
  
   System() = default;
   virtual ~System() = default;

  static A*& Instance()
  {
    static A* m_instance = nullptr;
    return m_instance;
  }

  

  static bool IsStarted()
  {
    return Instance() ? true : false;
  }

};
