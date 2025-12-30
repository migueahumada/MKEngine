#pragma once

#include "PrerequisitesCore.h"

#include <fstream>

class mkImage
{

public:
  mkImage() = default;
  ~mkImage() = default;

private:

  void load();
  void encode();

};

