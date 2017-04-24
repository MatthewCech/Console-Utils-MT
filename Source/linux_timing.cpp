// Win and Linux
#include <string>
#include <sstream>
#include <iostream>
#include <cstdio>
#include <vector>
#include <iomanip>  

// Timing
#include <chrono>
#include <iostream>
#include <vector>
#include <numeric>
#include <string>
#include <functional>

// Linux specifically
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>

  ////////////
 // Colors //
////////////
const char* COLOR_CLS = "\033[2J";
const char* COLOR_BLACK = "\033[22;30m";
const char* COLOR_RED = "\033[22;31m";
const char* COLOR_GREEN = "\033[22;32m";
const char* COLOR_BROWN = "\033[22;33m";
const char* COLOR_BLUE = "\033[22;34m";
const char* COLOR_MAGENTA = "\033[22;35m";
const char* COLOR_CYAN = "\033[22;36m";
const char* COLOR_GREY = "\033[22;37m";
const char* COLOR_DARKGREY = "\033[01;30m";
const char* COLOR_LIGHTRED = "\033[01;31m";
const char* COLOR_LIGHTGREEN = "\033[01;32m";
const char* COLOR_YELLOW = "\033[01;33m";
const char* COLOR_LIGHTBLUE = "\033[01;34m";
const char* COLOR_LIGHTMAGENTA = "\033[01;35m";
const char* COLOR_LIGHTCYAN = "\033[01;36m";
const char* COLOR_WHITE = "\033[01;37m";


void clear()
{
  printf("\033[2J\033[H");
}

void print(int x, int y, char buf, const char* colorCode = "")
{
  printf("%s\033[%d;%dH%c\n", colorCode, x, y, buf);
}

int main()
{
  const double size = 200;
  bool looped = false;
  int index = 0;
  double times[static_cast<int>(size)] = { 0 };

  while(1)
  {  
    struct winsize screenSize;
    ioctl(STDOUT_FILENO,TIOCGWINSZ,&screenSize);

    // Timer Start ////////////////////////////////////////////////////////////
    auto start = std::chrono::high_resolution_clock::now();

    for(int i = 0; i < screenSize.ws_row; ++i)
      for(int j = 0; j < screenSize.ws_col; ++j)
        print(i, j, 219, COLOR_LIGHTCYAN);

    // Timer end, and accumulation after. Not included. ///////////////////////
    auto finish = std::chrono::high_resolution_clock::now();
    times[index++] = std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count() / 1000000.0;
    if(index >= size)
      looped = true, index = 0;

    double sum = 0;
    for(int i = 0; i < size; ++i)
      sum += times[i];

    std::cout << "ms: " << std::left << std::setw(10) << sum / size << std::right 
    << ", averaging at " << std::setw(4) << std::left 
    << (looped ? 100 :  index / size * 100) 
    << std::right << "%" << '\n';
  }

  return 0;
}