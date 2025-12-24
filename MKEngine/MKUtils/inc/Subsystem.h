#pragma once
#include <utility>
#include <assert.h>

/**
* Module pattern by Samuel A. Prince Quezada
* Takes advantage of static variables allocated in the heap 
* within static functions, CRTP, inheritance and variadic templates.
*/

template <class A>
class Subsystem
{
 public:
  
  template<typename... Args>
  static void StartUp(Args&&... args)
  {
    assert(!IsStarted() && "Instance has been already started up.");
    Instance() = new A(std::forward<Args>(args)...);
    
    IsStarted() = true;

    static_cast<Subsystem*>(Instance())->OnStartUp();
  }

  template<class Subtype, typename... Args>
  static void StartUp(Args&&... args)
  {
    static_assert(std::is_base_of<A, Subtype>::value,
      "Provided type isn't derived from type the Module is initialized with.");

    assert(!IsStarted() && "Instance has been already started up.");
    Instance() = new Subtype(std::forward<Args>(args)...);

    IsStarted() = true;
  }
  
  static void ShutDown()
  {
    assert(IsStarted()  && "No Instance exists, there's nothing to shutdown");
    
    delete(Instance());
    Instance() = nullptr;

    IsStarted() = false;
  }

  static A& GetInstance()
  {
    return *Instance();
  }

  static bool& IsStarted()
  {
    static bool isStarted = false;
    return isStarted;
  }

 protected:
   virtual void OnStartUp() {}
   virtual void OnShutDown() {}
  
  Subsystem() = default;
  virtual ~Subsystem() = default;

  Subsystem(const Subsystem&) = delete;
  Subsystem(Subsystem&&) = delete;

  Subsystem& operator=(const Subsystem&) = delete;
  Subsystem& operator=(Subsystem&&) = delete;

  static A*& Instance()
  {
    static A* m_instance = nullptr;
    return m_instance;
  }
};