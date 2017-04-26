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

namespace Coloring
{
  const char* COLORCODE_BLACK = "\033[22;30m";
  const char* COLORCODE_RED = "\033[22;31m";
  const char* COLORCODE_GREEN = "\033[22;32m";
  const char* COLORCODE_BROWN = "\033[22;33m";
  const char* COLORCODE_BLUE = "\033[22;34m";
  const char* COLORCODE_MAGENTA = "\033[22;35m";
  const char* COLORCODE_CYAN = "\033[22;36m";
  const char* COLORCODE_GREY = "\033[22;37m";
  const char* COLORCODE_DARKGREY = "\033[01;30m";
  const char* COLORCODE_LIGHTRED = "\033[01;31m";
  const char* COLORCODE_LIGHTGREEN = "\033[01;32m";
  const char* COLORCODE_YELLOW = "\033[01;33m";
  const char* COLORCODE_LIGHTBLUE = "\033[01;34m";
  const char* COLORCODE_LIGHTMAGENTA = "\033[01;35m";
  const char* COLORCODE_LIGHTCYAN = "\033[01;36m";
  const char* COLORCODE_WHITE = "\033[01;37m";

  enum
  {
    COLOR_BLACK = 0, COLOR_BLUE, COLOR_GREEN, COLOR_CYAN,
    COLOR_RED, COLOR_MAGENTA, COLOR_BROWN, COLOR_GREY,
    COLOR_DARKGREY, COLOR_LIGHTBLUE, COLOR_LIGHTGREEN,
    COLOR_LIGHTCYAN, COLOR_LIGHTRED, COLOR_LIGHTMAGENTA,
    COLOR_YELLOW, COLOR_WHITE, COLOR_ENUM_GET_LENGTH
  };

  const char* GetColor(int color)
  {
    switch (color)
    {
    case 0: return COLORCODE_BLACK;
    case 1: return COLORCODE_BLUE;
    case 2: return COLORCODE_GREEN;
    case 3: return COLORCODE_CYAN;
    case 4: return COLORCODE_RED;
    case 5: return COLORCODE_MAGENTA;
    case 6: return COLORCODE_BROWN;
    case 7: return COLORCODE_GREY;
    case 8: return COLORCODE_DARKGREY;
    case 9: return COLORCODE_LIGHTBLUE;
    case 10: return COLORCODE_LIGHTGREEN;
    case 11: return COLORCODE_LIGHTCYAN;
    case 12: return COLORCODE_LIGHTRED;
    case 13: return COLORCODE_LIGHTMAGENTA;
    case 14: return COLORCODE_YELLOW;
    case 15: return COLORCODE_WHITE;
    }

    return "";
  }
}

void Clear()
{
#ifdef _WIN32
  system("cls");
#else 
  printf("\033[2J\033[H");
#endif
}

void Print(int x, int y, unsigned char buf, int colorCode = 9)
{
#ifdef _WIN32
  // In theory, there is a way to do this for windows using the printf in the #else.
  COORD coord{ (SHORT)x - 1, (SHORT)y - 1 };                        // Pos                                        
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); // Pos
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);                // Color
  SetConsoleTextAttribute(hConsole, static_cast<WORD>(colorCode));  // Color
  printf("%c", buf);
#else
  // Pos and color
  printf("%s\033[%d;%dH%c\n", Coloring::GetColor(colorCode), x, y, buf);
#endif
}

void GetScreenSize(int &width, int &height)
{
  #ifdef _WIN32 // May be off by 1. 
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi); // Returns -1 on failure.
    width = csbi.srWindow.Right - csbi.srWindow.Left + 1; 
    height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
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
  const int size = 100;
  double times[size] = { 0 };
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
    GetScreenSize(width, height);

    // Draw the screen. Height offset by 1 to print stats at the end.
    for(int i = 0; i < width; ++i)
      for(int j = 0; j < height - 1; ++j)
        Print(i, j, static_cast<unsigned char>(219), Coloring::COLOR_LIGHTCYAN);



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
  }

  // Return normal
  return 0;
}