#pragma once

class DrawThreadData
{
public:
  // Data to init the thread
  const int _id;

  // Data for the drawing process
  const int _start_x;
  const int _start_y;
  const int _range_x;
  const int _range_y;

  // Data that could be shared with the main thread
  int timeAvg;

  // CTR
  DrawThreadData(int id, int start_x, int start_y, int range_x, int range_y)
    : _id(id)
    , _start_x(start_x)
    , _start_y(start_y)
    , _range_x(range_x)
    , _range_y(range_y)
    , timeAvg(0)
  {}

};
