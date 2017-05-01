#pragma once

#include "utilities.hpp"


#define MAX_RGB 6

struct RGBColor
{
  char r;
  char g;
  char b;

  typedef const char *ColorString;
  static const ColorString ColorCodeLookup[];



  inline unsigned char GetIndex()
  {
    return RGBColor::RGBIndex(r, g, b);
  }

  static inline unsigned char RGBIndex(char r, char g, char b)
  {
    r = posMod(r, MAX_RGB);
    g = posMod(g, MAX_RGB);
    b = posMod(b, MAX_RGB);
    return r*36 + g*6 + b + 16;
  }

  static inline const char* RGBString(RGBColor color)
  {
    return ColorCodeLookup[color.GetIndex()];
  }
};
