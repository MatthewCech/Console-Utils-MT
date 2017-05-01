#pragma once

#include <utility> // pair
#include "RGBColor.hpp"
#include <exception>
#include <string>

//#define VALIDATE_COORDS

#ifdef VALIDATE_COORDS
#define ASSERT_X(v) AssertX(v)
#define ASSERT_Y(v) AssertY(v)
#else
#define ASSERT_X(v)
#define ASSERT_Y(v)
#endif


// Pack all chars so we can treat it as string
#pragma pack(push, 1)
struct CanvasElement
{
  //  "\033[38;5;@@@m" <-- Foreground ANSI Data
  char meta_CSI_1[2]  = {'\033','['};
  char meta_SGR_1[5]  = {'3','8',';','5',';'};
  char color_front[3] = {'2','3','2'}; // white
  char delim_1[1]     = {'m'};

  //  "\033[48;5;@@@m" <-- Background ANSI Data
  char meta_CSI_2[2]  = {'\033','['};
  char meta_SGR_2[5]  = {'4','8',';','5',';'};
  char color_back[3]  = {'2','3','4'}; // black
  char delim_2[1]     = {'m'};

  //  "@"
  char print_char    = ' ';

  // NO NULL TERM
};
#pragma pack(pop)



class Canvas
{
private:

public:
  // Bookkeeping
  int _width;           // actual width
  int _effective_width; // width without newlines
  int _height;          // actual height
  int _elementCount;    // width*height (includes newlines)

  // Buffers
  CanvasElement *_cleanBuff;
  CanvasElement *_buffer;

  Canvas(int width=80, int height=10);
  ~Canvas();


  // Re-inits the buffers with new width/height
  void UpdateBufferSize(int width, int height);
  // Copies the clean buffer over our current buffer
  void ResetBuffer();

  // Dump the buffer as a character array (not CanvasElement array)
  char *GetBuffer();

  // Helper for converting between 2d array x/y and 1d array index
  int CoordToIndex(int x, int y);
  std::pair<int, int> IndexToCoord(int index);

  void SetChar(int x, int y, char c);
  void SetChar(int index, char c);

  void SetColor(int x, int y, RGBColor foreground, RGBColor background = {-1});
  void SetColor(int index, RGBColor foreground, RGBColor background = {-1});

  void SetString(int x, int y, const char* str);
  void SetString(int index, const char* str);

  void SetColorMany(int x, int y, int count, RGBColor foreground, RGBColor background = {-1});
  void SetColorMany(int index, int count, RGBColor foreground, RGBColor background = {-1});

  void AssertX(int x);
  void AssertY(int y);
};

struct CanvasBoundException : public std::exception
{
   std::string s;
   CanvasBoundException(std::string ss) : s(ss) {}
   ~CanvasBoundException() throw () {} // Updated
   const char* what() const throw() { return s.c_str(); }
};

