// A color structure that stores the R, G, and B values
// for a specific index, in terms of 0-5. This is 
// the format required for 256-Color.
#pragma once
struct ColorRGB
{
  ColorRGB();
  ColorRGB(char r, char g, char b, bool isValid = true);
  void Set(char r, char g, char b, bool isValid = true);
  void Invalidate();

  char R;       // 0-5 Red 256-Color value. Higher is capped.
  char G;       // 0-5 Green 256-Color value. Higher is capped.
  char B;       // 0-5 Blue 256-Color value. Higher is capped.
  bool IsValid; // Has this color been adjusted? (Is drawn?)

private:
  char wrap(char val, char max);
};



// Contains two color attributes to be used by the attributes 
// data structure of the Frame object.
struct Attribute
{
  ColorRGB Foreground; // Color of the character in the foreground
  ColorRGB Background; // Color of space behind the character.
};
