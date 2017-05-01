#pragma once
#include "FrameManager.hpp"
#include "RGBColor.hpp"
#include "utilities.hpp"
#include "util_makeTestWindow.hpp"

#include <chrono>
#include <thread>

void DoMultiThreadTest(int threadCount)
{
  printf("ABOUT TO RUN WITH %d THREADS...\n\n", threadCount);

  std::this_thread::sleep_for (std::chrono::seconds(2));

  
  printf("RUN CODE HERE!\n");

  return;
}
