#pragma once

struct ThreadGlobals
{
  // If threads are allowed to start
  bool shouldRun;

  int width;
  int height;

  // Timing
  static const int size = 100;
  double times[size] = { 0 };
  bool looped = false;
  int index = 0;

  ThreadGlobals() 
    : shouldRun(false)
    , width(0)
    , height(0)
  {}
};
