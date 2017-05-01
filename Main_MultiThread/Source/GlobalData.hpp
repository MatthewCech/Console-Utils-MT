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
  double Time;
};

extern GlobalData Globals;
