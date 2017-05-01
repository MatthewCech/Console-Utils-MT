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


const char ColorCodeLookup[][] = {
  #include
}


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



void SetAttribute(char* attribute, char* colorFore, char* colorBack, char toPrint)
{
  int offset_colorFore =  7; // index 7-9
  int offset_colorBack = 18; // index 18-20
  int offset_printChar = 22; // index 22

  memcpy(attribute + offset_colorFore, colorFore, 3*sizeof(char));
  memcpy(attribute + offset_colorBack, colorBack, 3*sizeof(char));
  attribute[offset_printChar] = toPrint;
}




int main(int argc, char const *argv[])
{
  printf("[48;005;%03dm%s\n",123,"-");
  printf("[48;005;%03dm%s\n",1,"-");

  // 256 color mode for background
  const char* colorBack256 = "\033[48;005;%03dm%s";
  // 256 color mode for foreground
  const char* colorFront256 = "\033[38;005;%03dm%s";

  const char* testText = "Test   Text!!!\n";

  // background
  printf(colorBack256,  RGBIndex(5,0,0), testText);
  printf(colorFront256, RGBIndex(0,5,0), testText);
  printf(colorBack256,  RGBIndex(0,0,5), testText);
  printf(colorFront256, RGBIndex(5,4,0), testText);
  SetClear("\n");

  // Attribute Layout
  const char* colorLayout[] = {
    "\033[",  // CSI (control sequence introducer)
    "38;5;", 
              // [2-3] color - 38:foreground, 48:background
              // (5)   use rgb
    "%03dm"   // [8-11] color value - 0-256
  };


  std::string attributeFormat = "\033[38;5;%03dm\033[48;5;%03dm%s";

  // @ symbols need to be overwritten!
  char attributeChunk[] = "\033[38;5;@@@m\033[48;5;@@@m@";

  char *colorOne = (char *)"196";
  char *colorTwo = (char *)"051";
  char toPrint = 'X';




  SetAttribute(attributeChunk, colorOne, colorTwo, toPrint);
  printf("%s", attributeChunk);
  SetClear("\n");

  toPrint = 'A';
  SetAttribute(attributeChunk, colorTwo, colorOne, toPrint);

  printf("%s", attributeChunk);
          

  SetClear("\n");

  return 0;
}
