#include "DummyAPI.h"

DummyAPI& g_dummyAPI()
{
    return DummyAPI::GetInstance();
}
