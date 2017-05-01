#include "Canvas.hpp"
#include <cstring>
#include <stdio.h>

// generate statics

Canvas::Canvas(int width, int height)
  : _width(width)
  , _height(height)
  , _elementCount(_width*_height)
  , _cleanBuff(nullptr)
  , _buffer(nullptr)
{
  UpdateBufferSize(_width, _height);
}

Canvas::~Canvas()
{
  if(_cleanBuff) delete[] _cleanBuff;
  if(_buffer) delete[] _buffer;
}



void Canvas::UpdateBufferSize(int width, int height)
{
  _width = width;
  _height = height;
  _elementCount = _width*_height;

  if(_cleanBuff) delete[] _cleanBuff;
  _cleanBuff = new CanvasElement[_elementCount+1];
  // The last element acts as null terminator
  
  _cleanBuff[_elementCount].meta_CSI_1[0] = '\0';

  // initialize the newlines
  for(int index = 0; index < _elementCount; ++index)
    if(index%_width == _width-1) 
      _cleanBuff[index].print_char = '\n';

  // reset characters, etc on last newline
  //CanvasElement& last = _cleanBuff[_elementCount-1];  

  // Copy the clean buffer over our normal buffer
  ResetBuffer();
}

// Copies the clean buffer over the current buffer
void Canvas::ResetBuffer()
{
  if(_buffer) delete[] _buffer;
  _buffer = new CanvasElement[_elementCount+1];
  memcpy(_buffer, _cleanBuff, sizeof(CanvasElement)*(_elementCount+1));
}

char *Canvas::GetBuffer()
{
  return reinterpret_cast<char*>(_buffer);
}


// 2d->1d
int Canvas::CoordToIndex(int x, int y) 
{
  ASSERT_X(x);
  ASSERT_Y(y);

  // TODO: X/Y Assertion
  return x+_width*y;
}

// 1d->2d
std::pair<int, int> Canvas::IndexToCoord(int index)
{
  // TODO: Index Assertion
  return std::make_pair(index%_width, index/_width);
}

// Setting individual Characters
void Canvas::SetChar(int x, int y, char c) {
  if(x < 0 || y < 0 || x > _width-2 || y > _height -1) return;
  _buffer[CoordToIndex(x,y)].print_char = c;
}
void Canvas::SetChar(int index, char c) {
  if(index < 0 || index > _elementCount-1 || (index % _width == _width-1)) return;
  _buffer[index].print_char = c; 
}

void Canvas::SetColor(int x, int y, RGBColor foreground, RGBColor background)
{
  SetColor(CoordToIndex(x,y), foreground, background);
}

void Canvas::SetColor(int index, RGBColor foreground, RGBColor background)
{
  if(foreground.R >= 0)
  {
    const char* color_fore = RGBColor::RGBString(foreground);
    memcpy(_buffer[index].color_front, color_fore, sizeof(char)*3);
  }

  if(background.R >= 0)
  {
    const char* color_back = RGBColor::RGBString(background);
    memcpy(_buffer[index].color_back,  color_back, sizeof(char)*3);
  }
}


// Setting a whole string
void Canvas::SetString(int x, int y, const char* str) 
{ 
  SetString(CoordToIndex(x, y), str); 
}
void Canvas::SetString(int index, const char* str) 
{
  int remain = _elementCount - index;
  for(int i = 0; i < remain; ++i)
  {
    if((index+i)%_width == _width-1)
    {
      --remain;
      continue;
    }
    // return if we hit the end of the string
    if(str[i] == '\0') return;
    _buffer[index+i].print_char = str[i];
  }
}

void Canvas::SetColorMany(int x, int y, int count, RGBColor foreground, RGBColor background)
{
  SetColorMany(CoordToIndex(x,y), count, foreground, background);
}

void Canvas::SetColorMany(int index, int count, RGBColor foreground, RGBColor background)
{
  // negative means fill to end.
  if(count == -1) count = _elementCount;
  int remain = _elementCount - index;
  for(int i = 0; i < remain; ++i)
  {
    if((index+i)%_width == _width-1)
    {
      //remain;
      continue;
    }
    // return if we hit the end of the string
    if(i >= count) return;
    SetColor(index+i, foreground, background);
  }
}


void Canvas::AssertX(int x)
{
  if(x < 0 || x > _width-2)
    throw CanvasBoundException("INVALID X");
}

void Canvas::AssertY(int y)
{
  if(y < 0 || y > _width-2)
    throw CanvasBoundException("INVALID Y");
}
