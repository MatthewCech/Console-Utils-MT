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

  FrameManager manager(0, -3, threadCount);
  makeTestWindow(manager, 10, 3, 0);
  makeTestWindow(manager, 20, 8, 1);
  int loops = 2000;
  while (loops-->0)
  {
    manager.Update();
  }
  std::this_thread::sleep_for (std::chrono::seconds(2));

  //printf("RUN CODE HERE!\n");

  return;
}
