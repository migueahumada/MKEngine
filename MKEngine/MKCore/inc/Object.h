#pragma once
#include "PrerequisitesCore.h"

/**
*
*/

class Object
{
 
 public:
  Object() = default;
  virtual ~Object() = default;

  MK_GUID getGUID()
  {
    return m_guid;
  }

 protected:

  
  
  MK_GUID m_guid = 234;
  
};

