#include <stdio.h>
#include <cstdlib>

#define MAX_MODE 55
#define MIN_COLOR 0
#define MAX_COLOR 107
#define MAX_RGB 6

const char* modeFormat = "\033[%02d;%02dm%s";

// 256 color mode for background
const char* colorBack256 = "\033[48;05;%dm%s";
// 256 color mode for foreground
const char* colorFront256 = "\033[38;05;%dm%s";


inline int posMod(int val, int max)
{
  val = (val%max);
  if(val < 0) val+=max;
  return val;
}

void SetClear(const char* text = "")
{
  printf(modeFormat, 0, 0, text);
}

void SetMode(int sgr, int color, const char* text = "")
{
  sgr = posMod(sgr, MAX_MODE);
  color = posMod(color, MAX_MODE);
  printf(modeFormat, sgr, color, text);
}


void SetColor(int r, int g, int b, bool background = true, const char* text = "")
{
  r = posMod(r, MAX_RGB);
  g = posMod(g, MAX_RGB);
  b = posMod(b, MAX_RGB);

  int color = r*36 + g*6 + b + 16;
  
  if(background)
    printf(colorBack256, color, text);
  else
    printf(colorFront256, color, text);
}


void testModes()
{
  const char *test_text = "XXX";

  printf("ITERATING OVER POSSIBLE MODES:\n");
  printf("\t(each 'XXX' is printed with the given modes)\n");
  for(int code = 0; code < MAX_MODE; ++code)
  {
    for(int color = MIN_COLOR; color < MAX_COLOR; ++color)
    {
      // Reset color
      printf("\t[%02d;%03.2d]: ", code, color);

      // Start test line
      printf(modeFormat, 22, 31, "R");
      printf(modeFormat, code, color, test_text);
      printf(modeFormat, 22, 32, "G");
      printf(modeFormat, code, color, test_text);
      printf(modeFormat, 22, 36, "B");
      printf(modeFormat, code, color, test_text);

      SetClear();
      if(color%3 == 2)
        printf("\n");
    }
    printf("\n\n");
  }
  printf("\nDONE.\n");
}

void testColors()
{
  const char* test_text = "COLOR: \t\t[r:%d, g:%d, b:%d]";

  SetClear("\n\nCOLORS:\n");
  for(int r = 0; r < 6; ++r)
  {
    for(int g = 0; g < 6; ++g)
    {
      for(int b = 0; b < 6; ++b)
      {
        SetClear("\t");
        SetColor(r,g,b, false);
        printf(test_text, r, g, b);
        SetClear("\n\t");
        SetColor(r,g,b, true, "");
        printf(test_text, r, g, b);
        SetClear("\n");
      }
      printf("\n");
    }
    printf("\n");
  }
}


void (*pTests[])() = { 
    testModes,
    testColors
}; 




int main(int argc, char const *argv[])
{
  int testCount = sizeof(pTests)/sizeof(pTests[0]);

  int maxMode = MAX_MODE-1;
  int maxColor = MAX_RGB-1;

  int arg1 = 0;
  int arg2 = 0;
  int arg3 = 0;

  const char* testText = "___  TEST 123  ___";

  // Grab args
  switch(argc)
  {
  case 4: arg3 = atoi(argv[3]);
  case 3: arg2 = atoi(argv[2]);
  case 2: arg1 = atoi(argv[1]);
  }

  // Handle args
  switch(argc)
  {
  // no args
  case 1:
    printf("You can use the following arguments:\n");
    printf("\t1 arg: \t%s <TestNumber:0-%d>\n", argv[0], testCount);
    printf("\t2 arg: \t%s <sgr:0-%d> <color:0-%d>\n", argv[0], maxMode, maxMode);
    printf("\t3 arg: \t%s <R:0-%d> <G:0-%d> <B:0-%d>\n", argv[0], maxColor, maxColor, maxColor);
    break;

  // 1 arg - run test
  case 2:
    printf("COUNT: %d\n", posMod(arg1, testCount));
    arg1 = posMod(arg1, testCount);
    printf("running test #%d:\n", arg1);
    pTests[arg1]();
    break;

  // 2 args - set modes
  case 3:
    SetClear();
    printf("Using Mode \\033[%d;%dm :\n\t", arg1, arg2);
    SetMode(arg1, arg2, testText);
    break;

  // 3 args - use rgb colors
  case 4:
    SetClear();
    printf("Using Color <r:%d,g:%d,b:%d>:\n\t", arg1, arg2, arg3);
    
    printf("FRONT: ");
    SetColor(arg1, arg2, arg3, false, testText);
    SetClear("\n\t");

    printf(" BACK: ");
    SetColor(arg1, arg2, arg3, true, testText);
    break;

  }

  SetClear("\n");
  return 0;
}
