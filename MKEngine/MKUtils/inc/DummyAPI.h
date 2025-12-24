#pragma once
#include "PrerequisitesUtils.h"
#include "Subsystem.h"

class MK_UTILS_API DummyAPI : public Subsystem<DummyAPI>
{
 public:
  explicit DummyAPI(int num);
  virtual ~DummyAPI() = default;
 
  inline int getNum(){ return m_num;}
   
 protected:
  
   virtual void OnStartUp() override;
   virtual void OnShutDown() override;

  int m_num = 2;
};

DummyAPI& g_dummyAPI();

