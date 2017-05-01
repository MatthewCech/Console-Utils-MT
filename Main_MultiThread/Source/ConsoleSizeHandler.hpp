#pragma once

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

  while(Globals.threadsCanRun)
  {
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &screenSize);

    Globals.width = screenSize.ws_col;
    Globals.height = screenSize.ws_row;

    std::this_thread::sleep_for (std::chrono::milliseconds(delay));
  }
}
