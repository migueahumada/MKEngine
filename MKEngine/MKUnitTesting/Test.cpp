
#include "Singleton.h"
#include <iostream>



int main()
{
  Singleton::StartUp();
  
  std::cout << Singleton::GetInstance().getNum() << std::endl;

  std::cout << Singleton::GetInstance().getBool() << std::endl;

  g_Singleton().getBool();

  Singleton::Shutdown();

  return 0;
}