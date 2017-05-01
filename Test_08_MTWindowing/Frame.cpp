#include <stdio.h>
#include <string.h>
#include <memory>
#include "Frame.hpp"
#include "FrameManager.hpp"


// Non-default Ctor, takes an offset and a size + unique ID.
// ID can NOT be changed post-construction.
Frame::Frame(int id, FrameManager *m, int x, int y, int width, int height, int layer) 
 : _posX(x)
 , _posY(y)
 , _width(width)
 , _height(height)
 , _layer(layer)
 , _id(id)
 , _bufferSize(width * height)
 , _bufferChar(new char[_bufferSize + 1])
 , _bufferAttributes(new Attribute[_bufferSize])
 , _manager(m)
{
  clearBuffers();
}


Frame::~Frame()
{
  delete[] _bufferChar;
  delete[] _bufferAttributes;
}

// Writes char <c> to position (<x>, <y>) and gives the
// character color <fg>, and the background the color <bg>.
void Frame::Write(char c, int x, int y, ColorRGB fg, ColorRGB bg)
{
  Write(&c, 1, x, y, fg, bg);
}

// Writes a buffer of <size> starting at position (<x>, <y>) 
// and gives the character color <fg>, and the background the color <bg>.
// User must guarentee <buf> is at least <size> large. Undefined
// behavior may result otherwise.
void Frame::Write(const char *buf, int size, int x, int y, ColorRGB fg, ColorRGB bg)
{
  // No starting drawing outside the frame.
  if(!inRange(x, 0, _width - 1))
    return;//    throw "X out of range!";
  
  if(!inRange(y, 0, _height - 1))
    return;//    throw "Y out of range!";
  
  // Draw as long as we can inside the frame with the buffer.
  for(int i = 0; i < size; ++i)
  {
    const int pos = y * _width + x + i;
    if(pos > _bufferSize - 1)
      break;

    _bufferChar[pos] = buf[i];
    _bufferAttributes[pos].Foreground = fg;
    _bufferAttributes[pos].Background = bg;
  }
}

// Silly function to add a border.
void Frame::AddBorder(ColorRGB fg, ColorRGB bg)
{
  for(int x = 0; x < _width; ++x)
    for(int y = 0; y < _height; ++y)
    {
      if(x == 0 || x == _width - 1)
        Write('|', x, y, fg, bg);

      if(y == 0 || y == _height - 1)
      {
        if(x == 0 || x == _width - 1)
          Write('+', x, y, fg, bg);
        else
          Write('-', x, y, fg, bg);
      }
    }
}

// Repositions the window in the canvas.
// Size does not change.
void Frame::SetLocation(int x, int y)
{
  _posX = x;
  _posY = y;
  _manager->updateOrderingBuffer();
  //throw __func__;
}

// Sets the size of the window by adjusting width and height.
// Position does not change.
void Frame::SetSize(int width, int height)
{
  initBuffers();
  throw __func__;
}

// Sets the layer of the current frame.
void Frame::SetLayer(int newLayer)
{
  _layer = newLayer;
  throw __func__;
}

int Frame::PosX() const
{
  return _posX;
}
int Frame::PosY() const
{
  return _posY;
}
int Frame::Width() const
{
  return _width;
}
int Frame::Height() const
{
  return _height;
}
int Frame::Layer() const
{
  return _layer;
}

// Initializes the buffers again with the provided width and height.
void Frame::initBuffers()
{
  _bufferSize = _width * _height;
  delete[] _bufferChar;
  delete[] _bufferAttributes;
  _bufferChar = new char[_bufferSize + 1];
  _bufferAttributes = new Attribute[_bufferSize];
  clearBuffers();
}

void Frame::clearBuffers()
{
  memset(_bufferChar, ' ', _bufferSize);
  memset(_bufferAttributes, 0, _bufferSize);
  _bufferChar[_bufferSize] = '\0';
}

// Private member function that uses threads to translate
// the contents of our proprietary storage to the actual
// canvas frame buffer.
void Frame::translateToCanvas() const
{
  // Does stuff.
}

// Returns the ID of this frame.
int Frame::ID() const
{
  return _id;
}

inline bool Frame::inRange(int val, int min, int max)
{
  if(val < min || val > max)
    return false;
  return true;
}

int Frame::wrap(int val, int max)
{
  val = (val % max);
  if(val < 0) 
    val += max;

  return val;
}
