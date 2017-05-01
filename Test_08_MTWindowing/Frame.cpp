#include <stdio.h>
#include <string.h>
#include "Frame.hpp"



// Non-default Ctor, takes an offset and a size + unique ID.
// ID can NOT be changed post-construction.
Frame::Frame(int id, int x, int y, int width, int height ) 
 : _posX(x)
 , _posY(y)
 , _width(width)
 , _height(height)
 , _id(id)
 , _bufferSize(width * height)
 , _bufferChar(new char[_bufferSize])
 , _bufferAttributes(new Attribute[_bufferSize])
 {  }


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
void Frame::Write(char *buf, int size, int x, int y, ColorRGB fg, ColorRGB bg)
{
  // No drawing outside the frame.
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

// Repositions the window in the canvas.
// Size does not change.
void Frame::Relocate(int x, int y)
{
  throw __func__;
}

// Sets the size of the window by adjusting width and height.
// Position does not change.
void Frame::SetSize(int width, int height)
{
  initBuffers();
  throw __func__;
}

int Frame::Width() const
{
  return _height;
}
int Frame::Height() const
{
  return _height;
}
int Frame::PosX() const
{
  return _posX;
}
int Frame::PosY() const
{
  return _posY;
}

// Initializes the buffers again with the provided width and height.
void Frame::initBuffers()
{
  _bufferSize = _width * _height;
  delete[] _bufferChar;
  delete[] _bufferAttributes;
  _bufferChar = new char[_bufferSize];
  _bufferAttributes = new Attribute[_bufferSize];
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

bool Frame::inRange(int val, int min, int max)
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
