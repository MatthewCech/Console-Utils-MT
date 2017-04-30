#include "MainTest.hpp"
#include "ThreadData/ThreadGlobals.hpp"
#include "ThreadData/DrawThreadData.hpp"

/*
inline bool HandleResize()
{
  int last_width = width;
  int last_height = height ;

  // Set screen size
  GetScreenSize(width, height);

  // Screen resized
  if(last_width != width || last_height != height)
  {
    //looped = false;
    //index = 0;
    Clear();

    return true;
  }
  return false;
}
*/

/*
// Draws and returns avg
inline double DoDraw(
  int color, int symbol, 
  int start_x, int start_y, 
  int range_x, int range_y)
{
  //////////////////////////////////////////////////////////////
  // Timer Start ///////////////////////////////////////////////
  auto start = std::chrono::high_resolution_clock::now();    //
  ////////////////////////////////////////////////////////////

  char curChar = '0' + static_cast<char>(count++ % 10);

  // 1. get coords
  int end_x = data->_start_x + data->_range_x;
  int end_y = data->_start_y + data->_range_y;

  // 2. make sure they remain in limits
  end_x = (end_x > width) ? width : end_x;
  end_y = (end_y > height - 1) ? (height - 1) : end_y;

  // Draw the screen. Height offset by 1 to print stats at the end.
  for(int y = data->_start_y; y < end_y; ++y)
    for(int x = data->_start_x; x < end_x; ++x)
      Print(y, x, curChar , curColor);

  return std::chrono::high_resolution_clock::now() - start;
}
/ *
    //////////////////////////////////////////////////////////////
    // Timer End /////////////////////////////////////////////////
    auto finish = std::chrono::high_resolution_clock::now();   //
    ////////////////////////////////////////////////////////////
    #ifdef _WIN32 
      // Print trailing newline to make windows happy and wrap properly.
      printf("\n");
    #endif

    // Accumulate values after. Not incluided in the time.
    times[index++] = std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count() / 1000000.0;
    if(index >= size)
      looped = true, index = 0;

    double sum = 0;
    double len = looped ? size : index + 1;
    for (int i = 0; i < len; ++i)
      sum += times[i];

    // Print timing info
    std::cout 
      << std::left  << "ms: " << std::left << std::setw(10) << sum / len
      << std::right << ", avg over " << std::setw(4) << std::left << len
      << std::right << "samples.";
*/

/*
inline void DoThreadDraw(DrawThreadData *data, ThreadGlobals *globals)
{
  int count = 0;
  int curColor = Coloring::COLOR_LIGHTBLUE + data->_id;

  // Busy wait thread while we are not allowed to run yet
  while(!globals->shouldRun)
  {}

  // Primary loop
  while(globals->shouldRun)
  {
    data->TimerStart();
    data->DoDraw();
    data->TimerEnd();
  }
}
*/


inline void DoThreadResize(ThreadGlobals *globals)
{
  // Busy wait thread while we are not allowed to run yet
  while(!globals->shouldRun)
  {}

  // Primary loop
  while(globals->shouldRun)
  {

  }
}


int RunTest(int threadCount)
{
  UNUSED(threadCount);

  // Set up Globals
  ThreadGlobals globals;


  // Set up Thread data containers
  std::vector<DrawThreadData> drawThreadData;
  drawThreadData.reserve(threadCount);
  for(int i = 0; i < threadCount; ++i)
    drawThreadData.push_back(DrawThreadData(i, 15*i, 0, 10, 4));

  // Set up Draw Threads
  std::vector<std::thread> drawThreads;
  drawThreads.reserve(threadCount);
  //for(int i = 0; i < threadCount; ++i)
  //  drawThreads.push_back( std::thread(DoThreadDraw, &(drawThreadData[i]), &globals) );

  // Set up Resize Thread
  std::thread resizeThread(DoThreadResize, &globals);


  // Tell the threads that they may run
  globals.shouldRun = true;


  // Close down Threads
  //for(int i = 0; i < threadCount; ++i)
  //  drawThreads[i].join();

  resizeThread.join();

  // Return normal
  return 0;
}
