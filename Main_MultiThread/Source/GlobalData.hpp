#pragma once

#include <thread>

struct GlobalData
{
  bool threadsCanRun;
  std::thread sizeHandler;
  int width;
  int height;
  bool ThreadDebug;
  int Loops;
};

extern GlobalData Globals;
