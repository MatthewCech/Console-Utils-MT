#include "interface.hpp"


void Clear()
{
#ifdef _WIN32
  system("cls");
#else 
  printf("\033[2J\033[H");
#endif
}

void Print(int x, int y, unsigned char buf, int colorCode)
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
    height = screenSize.ws_row;
    width = screenSize.ws_col;
  #endif
}
