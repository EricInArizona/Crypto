// Copyright Eric Chauvin 2021 - 2022.


#include "ThreadEC.h"
#include <thread>
#include <chrono>


void ThreadEC::sleep( Int32 milli )
{
std::this_thread::sleep_for(
                      std::chrono::milliseconds(
                      milli ));
}
