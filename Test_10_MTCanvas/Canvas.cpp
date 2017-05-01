#include "Canvas.hpp"
#include <cstring>

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
  if(_cleanBuff) delete[] _cleanBuff;
  _cleanBuff = new CanvasElement[_elementCount+1];
  // The last element acts as null terminator
  _cleanBuff[_elementCount].meta_CSI_1[0] = '\0';

  // initialize the newlines
  for(int index = 0; index < _elementCount; ++index)
    if(index%_width == _width-1) 
      _cleanBuff[index].print_char = '\n';

  // Copy the clean buffer over our normal buffer
  ResetBuffer();
}

// Copies the clean buffer over the current buffer
void Canvas::ResetBuffer()
{
  if(_buffer) delete _buffer;
  _buffer = new CanvasElement[_elementCount+1];
  memcpy(_buffer, _cleanBuff, _elementCount+1);
}

char *Canvas::GetBuffer()
{
  return reinterpret_cast<char*>(_buffer);
}


// 2d->1d
inline int Canvas::CoordToIndex(int x, int y) 
{
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
void Canvas::SetChar(int x, int y, char c) { SetChar(CoordToIndex(x,y), c); }
inline void Canvas::SetChar(int index, char c) { _buffer[index].print_char = c; }

void Canvas::SetColor(int x, int y, RGBColor foreground, RGBColor background)
{
  SetColor(CoordToIndex(x,y), foreground, background);
}
inline void Canvas::SetColor(int index, RGBColor foreground, RGBColor background)
{
  const char* color_fore = RGBColor::RGBString(foreground);
  const char* color_back = RGBColor::RGBString(background);

  memcpy(_buffer[index].color_front, color_fore, sizeof(char)*3);
  memcpy(_buffer[index].color_back,  color_back, sizeof(char)*3);
}

// Setting a whole string
inline void Canvas::SetString(int x, int y, const char* str) 
{ 
  SetString(CoordToIndex(x, y), str); 
}
inline void Canvas::SetString(int index, const char* str) 
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