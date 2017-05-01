// A color structure that stores the R, G, and B values
// for a specific index, in terms of 0-5. This is 
// the format required for 256-Color.
struct ColorRGB
{
  ColorRGB() 
   : R(0)
   , G(0)
   , B(0)
   , IsValid(0) 
  {  }
  
  ColorRGB(char r, char g, char b, bool isValid = true)
   : R(r)
   , G(g)
   , B(b)
   , IsValid(isValid)
  {  }

  void Set(char r, char g, char b, bool isValid = true)
  {
    R = wrap(r, 5);
    G = wrap(g, 5);
    B = wrap(b, 5);
    IsValid = isValid;
  }

  void Invalidate()
  {
    IsValid = false;
  }

  char R;       // 0-5 Red 256-Color value. Higher is capped.
  char G;       // 0-5 Green 256-Color value. Higher is capped.
  char B;       // 0-5 Blue 256-Color value. Higher is capped.
  bool IsValid; // Has this color been adjusted? (Is drawn?)

private:
  char wrap(char val, char max)
  {
    val = (val % max);
    if(val < 0) 
      val += max;

    return val;
  }
};


// Contains two color attributes to be used by the attributes 
// data structure of the Frame object.
struct Attribute
{
  ColorRGB Foreground; // Color of the character in the foreground
  ColorRGB Background; // Color of space behind the character.
};
