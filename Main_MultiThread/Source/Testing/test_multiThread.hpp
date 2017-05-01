#pragma once
#include "FrameManager.hpp"
#include "RGBColor.hpp"
#include "utilities.hpp"
#include "util_makeTestWindow.hpp"

#include "GlobalData.hpp"

#include <chrono>
#include <thread>
#include <cstdlib>
#include <ctime>


inline int randRange(int min, int max) { return (std::rand() % (max-min)) + min; }

void DoMultiThreadTest(int threadCount, int windowCount = 12)
{
  // initialize rand
  std::srand(std::time(0));

  printf("ABOUT TO RUN WITH %d THREADS...\n\n", threadCount);

  // Scope to force destructor once we've received a sigterm
  {
    FrameManager manager(0, -4, threadCount);

    for(int i = 0; i < windowCount; ++i)
    {
      int left = randRange(1, Globals.width - 30);
      int top  = randRange(3, Globals.height - 15);

      RGBColor back  = { (char)randRange(0,3),       (char)randRange(0,3),       (char)randRange(0,3) };
      RGBColor front = { (char)randRange(back.R+1, 5), (char)randRange(back.G+1, 5), (char)randRange(back.B+1, 5) };

      makeTestWindow(manager, left, top, i, front, back);
    }
    
    while (Globals.threadsCanRun)
    {
      manager.Update();
      double avg = Globals.Time/Globals.Loops;  // ms per loop
      int fps = static_cast<int>(100/avg) * 10; // Loops per second (1000*ms) - rounded to nearest 10

      printf("\033[38;5;25m\033[%d;%dH[ Width: %4d |   Height: %4d |   %s %2d |   Windows: %3d |   DEBUG: %s ]\033[0m   \n",
        manager.ScreenHeight() + 2, 6, manager.ScreenWidth(), manager.ScreenHeight(), ((threadCount == 1) ? "Thread: " : "Threads:"), threadCount, windowCount, Globals.ThreadDebug ? " ENABLED" : "DISABLED");
      
      printf("\033[38;5;33m\033[%d;%dH[ Loops: %7d |   Time: %6.3f seconds |   Avg: %7.4f ms/loop |   FPS: %6d ]\033[0m   \n", 
        manager.ScreenHeight() + 3, 6, Globals.Loops, Globals.Time/1000, avg, fps);
    }
    // Destructor will now join all the threads
  }

  //std::this_thread::sleep_for (std::chrono::seconds(2));
  return;
}
