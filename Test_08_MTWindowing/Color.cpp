#include "Color.hpp"



ColorRGB::ColorRGB() 
 : R(0)
 , G(0)
 , B(0)
 , IsValid(0) 
{  }

ColorRGB::ColorRGB(char r, char g, char b, bool isValid)
 : R(r)
 , G(g)
 , B(b)
 , IsValid(isValid)
{  }

void ColorRGB::Set(char r, char g, char b, bool isValid)
{
  R = wrap(r, 5);
  G = wrap(g, 5);
  B = wrap(b, 5);
  IsValid = isValid;
}

void ColorRGB::Invalidate()
{
  IsValid = false;
}

char ColorRGB::wrap(char val, char max)
{
  val = (val % max);
  if(val < 0) 
    val += max;

  return val;
}

