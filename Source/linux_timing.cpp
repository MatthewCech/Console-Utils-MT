  //////////////////////
 // General Includes //
//////////////////////
// String manupulation
#include <string>
#include <iomanip>  
#include <sstream>
#include <iostream>
#include <cstdio>

// Timing
#include <chrono>
#include <numeric>
#include <functional>


  /////////////////
 // OS Specific //
/////////////////
#ifdef _WIN32
  // Windows
  #include <windows.h>
#else 
  // *Nix specifically
  #include <sys/ioctl.h>
  #include <stdio.h>
  #include <unistd.h>
#endif


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

void setSize(int &width, int &height)
{
  #ifdef _WIN32
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)
    width = csbi.srWindow.Right - csbi.srWindow.Left; // off by 1?
    height 
  #else
    struct winsize screenSize;
    ioctl(STDOUT_FILENO,TIOCGWINSZ,&screenSize);
    width = screenSize.ws_row;
    height = screenSize.ws_col;
  #endif
}

int main()
{
  // Timing
  const double size = 200;
  double times[static_cast<int>(size)] = { 0 };
  bool looped = false;
  int index = 0;

  // Sizing and Screen info
  int width = 0;
  int height = 0;

  // Primary loop
  while(true)
  {  
     //////////////////////////////////////////////////////////////
    // Timer Start ///////////////////////////////////////////////
    auto start = std::chrono::high_resolution_clock::now();    //
    ////////////////////////////////////////////////////////////




    // Set screen size
    setSize(width, height);

    // Draw the screen.
    for(int i = 0; i < width; ++i)
      for(int j = 0; j < height; ++j)
        print(i, j, 219, COLOR_LIGHTCYAN);




     //////////////////////////////////////////////////////////////
    // Timer End /////////////////////////////////////////////////
    auto finish = std::chrono::high_resolution_clock::now();   //
    ////////////////////////////////////////////////////////////

    // Accumulate values after. Not incluided in the time.
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

  // Return normal
  return 0;
}