#pragma once
#include "FrameManager.hpp"
#include "RGBColor.hpp"
#include "utilities.hpp"
#include "util_makeTestWindow.hpp"

#include "GlobalData.hpp"

#include <chrono>
#include <thread>

void DoMultiThreadTest(int threadCount)
{
  printf("ABOUT TO RUN WITH %d THREADS...\n\n", threadCount);

  // Scope to force destructor once we've received a sigterm
  {
    FrameManager manager(0, -3, threadCount);

    makeTestWindow(manager, 45, 5, -1);
    makeTestWindow(manager, 10, 2, 0);
    makeTestWindow(manager, 20, 8, 2);
    makeTestWindow(manager, 40, 15, 3);
    makeTestWindow(manager, 15, 19, 1);
    
    while (Globals.threadsCanRun)
      manager.Update();
    // Destructor will now join all the threads
  }

  //std::this_thread::sleep_for (std::chrono::seconds(2));
  return;
}
