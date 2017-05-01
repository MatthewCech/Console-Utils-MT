#pragma once

#include "FrameManager.hpp"
#include "RGBColor.hpp"
#include "utilities.hpp"
#include "util_makeTestWindow.hpp"
#include <string.h>
#include <string>
#include <chrono>
// rand
#include <cstdlib>
#include <stdlib.h>

void DoSinglethreadTest()
{
  // Timing
  const int size = 5000;
  double times[size] = { 0 };
  bool looped = false;
  int index = 0;

  // Frame manager initialization
  FrameManager manager(0, -3);
  int runIterations = 10000;
  const int numWindows = 3;
  const int countReset = 300;
  Frame *f[numWindows];
  int count = countReset;
  for(int i = 0; i < numWindows; ++i)
    f[i] = makeTestWindow(manager, rand() % manager.ScreenWidth(), rand() % manager.ScreenHeight(), i);


  int shuffle = 0;
  while(--runIterations)
  {
     //////////////////////////////////////////////////////////////
    // Timer Start ///////////////////////////////////////////////
    auto start = std::chrono::high_resolution_clock::now();    //
    ////////////////////////////////////////////////////////////

    if(--count == 0)
    {
      ++shuffle;
      shuffle = shuffle % 3;
      int x = rand() % manager.ScreenWidth();
      int y = rand() % manager.ScreenHeight();
      f[shuffle]->SetLocation(x, y);
      count = countReset;
    }

    manager.Update();


     //////////////////////////////////////////////////////////////
    // Timer End /////////////////////////////////////////////////
    auto finish = std::chrono::high_resolution_clock::now();   //
    ////////////////////////////////////////////////////////////

      // Accumulate values after. Not incluided in the time.
    times[index++] = std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count() / 1000000.0;
    if(index >= size)
      looped = true, index = 0;

    double sum = 0;
    double len = looped ? size : index + 1;
    for (int i = 0; i < len; ++i)
      sum += times[i];

    //printf("HJODSFKSDFIKSDNFKLJSLDJKNFJKLSDNFKSDF");
    // Print timing info
    printf("\033[38;5;555m\033[%d;%dH[ms: %f, avg over %d samples, remaining: %d]\n", manager.ScreenHeight() + 1, 6, sum / len, static_cast<int>(len), runIterations);
    /*std::cout x
      << std::left  << "ms: " << std::left << std::setw(10) << sum / len
      << std::right << ", avg over " << std::setw(4) << std::left << len
      << std::right << "samples." << '\n';
      */
  }
}
