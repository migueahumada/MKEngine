#include "DummyAPI.h"
#include "stdio.h"

DummyAPI::DummyAPI(int num) : m_num(num)
{
  
}

void DummyAPI::OnStartUp()
{
  printf("sTARITNG up DauumyAPI");
}

void DummyAPI::OnShutDown()
{
  printf("shutting down DauumyAPI");
}

