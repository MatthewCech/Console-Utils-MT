#pragma once

#include "utilities.hpp"


#define MAX_RGB 6

struct RGBColor
{
  char R;       // 0-5 Red 256-Color value. Higher is capped.
  char G;       // 0-5 Green 256-Color value. Higher is capped.
  char B;       // 0-5 Blue 256-Color value. Higher is capped.

  RGBColor(char r = 0, char g = 0, char b = 0)
    : R(r)
    , G(g)
    , B(b)
  {}

  typedef const char *ColorString;
  static const ColorString ColorCodeLookup[];

  inline void Set(char r, char g, char b)
  {
    R = posMod(r, MAX_RGB);
    G = posMod(g, MAX_RGB);
    B = posMod(b, MAX_RGB);
  }

  inline unsigned char GetIndex()
  {
    return RGBColor::RGBIndex(R, G, B);
  }

  inline void Invalidate()
  {
    R = -1;
    G = -1; 
    B = -1;
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


// Contains two color attributes to be used by the attributes 
// data structure of the Frame object.
struct Attribute
{
  RGBColor Foreground; // Color of the character in the foreground
  RGBColor Background; // Color of space behind the character.
};
