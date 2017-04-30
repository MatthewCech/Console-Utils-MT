#pragma once

namespace Coloring
{
  extern const char* COLORCODE_BLACK;
  extern const char* COLORCODE_RED;
  extern const char* COLORCODE_GREEN;
  extern const char* COLORCODE_BROWN;
  extern const char* COLORCODE_BLUE;
  extern const char* COLORCODE_MAGENTA;
  extern const char* COLORCODE_CYAN;
  extern const char* COLORCODE_GREY;
  extern const char* COLORCODE_DARKGREY;
  extern const char* COLORCODE_LIGHTRED;
  extern const char* COLORCODE_LIGHTGREEN;
  extern const char* COLORCODE_YELLOW;
  extern const char* COLORCODE_LIGHTBLUE;
  extern const char* COLORCODE_LIGHTMAGENTA;
  extern const char* COLORCODE_LIGHTCYAN;
  extern const char* COLORCODE_WHITE;

  enum
  {
    COLOR_BLACK = 0, COLOR_BLUE, COLOR_GREEN, COLOR_CYAN,
    COLOR_RED, COLOR_MAGENTA, COLOR_BROWN, COLOR_GREY,
    COLOR_DARKGREY, COLOR_LIGHTBLUE, COLOR_LIGHTGREEN,
    COLOR_LIGHTCYAN, COLOR_LIGHTRED, COLOR_LIGHTMAGENTA,
    COLOR_YELLOW, COLOR_WHITE, COLOR_ENUM_GET_LENGTH
  };

  inline const char* GetColor(int color)
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
