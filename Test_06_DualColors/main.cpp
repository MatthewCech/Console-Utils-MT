#include <stdio.h>
#include <cstdlib>
#include <string>
#include <cstring> // memcpy

#define MAX_MODE 55
#define MIN_COLOR 0
#define MAX_COLOR 107
#define MAX_RGB 6

const char* modeFormat = "\033[%02d;%03dm%s";
// 256 color mode for background
const char* colorBack256 = "\033[48;005;%03dm%s";
// 256 color mode for foreground
const char* colorFront256 = "\033[38;005;%03dm%s";

typedef const char *ColorString;
const ColorString ColorCodeLookup[] = {
  #include "colorLookup.inl"
};

// Attribute Layout
const char* colorLayout[] = {
  "\033[",  // CSI (control sequence introducer)
  "38;5;", 
            // [2-3] color - 38:foreground, 48:background
            // (5)   use rgb
  "%03dm"   // [8-11] color value - 0-256
};

const int offset_colorFore =  7; // index 7-9
const int offset_colorBack = 18; // index 18-20
const int offset_printChar = 22; // index 22



inline int posMod(int val, int max)
{
  val = (val%max);
  if(val < 0) val+=max;
  return val;
}


inline void SetClear(const char* text = "")
{
  printf(modeFormat, 0, 0, text);
}

inline void SetMode(int sgr, int color, const char* text = "")
{
  sgr = posMod(sgr, MAX_MODE);
  color = posMod(color, MAX_COLOR);
  printf(modeFormat, sgr, color, text);
}

inline unsigned char RGBIndex(char r, char g, char b)
{
  r = posMod(r, MAX_RGB);
  g = posMod(g, MAX_RGB);
  b = posMod(b, MAX_RGB);
  return r*36 + g*6 + b + 16;
}

inline void SetColor(int r, int g, int b, bool background = true, const char* text = "")
{
  int color = RGBIndex(r,g,b);
  
  if(background)
    printf(colorBack256, color, text);
  else
    printf(colorFront256, color, text);
}


void SetCharacter(char* attribute, char toPrint)
{
  attribute[offset_printChar] = toPrint;
}

void SetAttribute(char* attribute, unsigned char colorFore, unsigned char colorBack)
{
  memcpy(attribute + offset_colorFore, ColorCodeLookup[colorFore], 3*sizeof(char));
  memcpy(attribute + offset_colorBack, ColorCodeLookup[colorBack], 3*sizeof(char));
}



int main(int argc, char const *argv[])
{
  SetClear("\n");

  std::string attributeFormat = "\033[38;5;%03dm\033[48;5;%03dm%s";

  // @ symbols need to be overwritten!
  char symbolChunk[] = "\033[38;5;@@@m\033[48;5;@@@m@";
  const int symbolChunkSize = sizeof(symbolChunk)/sizeof(symbolChunk[0]) - 1;

  int width = 80;
  int height = 10;
  int effective_width = width-1;

  // bytesize of one line
  int symbolLineSize = width*symbolChunkSize;

  // Create Buffer
  char CanvasBuffer[symbolLineSize*height + 1];
  CanvasBuffer[symbolLineSize*height] = '\0'; // make sure it is null terminated!

  // Fill buffer with defaults
  for(int y = 0; y < height; ++y)
  {
    int curLine = symbolLineSize*y;
    for(int x = 0; x < width; ++x)
    {
      int curIndex = curLine + symbolChunkSize*x;
      // copy default values;
      memcpy(CanvasBuffer + curIndex, symbolChunk, symbolChunkSize);
      SetAttribute(CanvasBuffer + curIndex, RGBIndex(5,5,5), RGBIndex(0,0,0));

      if(x == effective_width)
        SetCharacter(CanvasBuffer + curIndex, '\n');
      else
        SetCharacter(CanvasBuffer + curIndex, ' ');
    }
  }


  int count = 0;
  int printed = -1;
  while(true)
  {
    
    for(int index = 0; index < width*height; ++index)
    {
      if(index%width != width-1)
      {
        SetCharacter(CanvasBuffer + index*symbolChunkSize, 'A' + (count)%26);
        char color = RGBIndex((count/36)%6, (count/6)%6, count%6);
        SetAttribute(CanvasBuffer + index*symbolChunkSize, RGBIndex(5,5,5), color);
      }
    }
    
    ++count;
    printf("\033[0;0H%s\n", CanvasBuffer);
    fflush(stdout);
  }


  return 0;
}
