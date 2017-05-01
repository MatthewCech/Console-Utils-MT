#pragma once
// Handles Console resizing, as well as run duration calculations


#include "GlobalData.hpp"

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <chrono>
#include <thread>


void Thread_CaptureConsoleSize(int delay)
{
  struct winsize screenSize;

  auto start = std::chrono::high_resolution_clock::now();  
  while(Globals.threadsCanRun)
  {
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &screenSize);
    
    auto now = std::chrono::high_resolution_clock::now();
    Globals.Time = std::chrono::duration_cast<std::chrono::nanoseconds>(now - start).count() / 1000000.0;

    Globals.width = screenSize.ws_col;
    Globals.height = screenSize.ws_row;
    std::this_thread::sleep_for (std::chrono::milliseconds(delay));
  }
}
