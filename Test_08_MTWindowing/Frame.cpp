#include <stdio.h>
#include <string.h>
#include "Frame.hpp"



// Non-default Ctor, takes an offset and a size + unique ID.
// ID can NOT be changed post-construction.
Frame::Frame(int id, int x, int y, int width, int height ) 
 : PosX(x)
 , PosY(y)
 , FrameWidth(width)
 , FrameHeight(height)
 , _id(id)
 , _bufferSize(width * height * (StepSize))
 , _buffer(new char[_bufferSize])
{
  for(int i = 0; i < _bufferSize; i += StepSize)
    memcpy(_buffer + i, "\033[22;32m!", StepSize);
}

// Writes a 
void Frame::Write(unsigned char c, int x, int y, ColorRGB)
{
  char buff[StepSize];
  sprintf(buff, "\033[22;31H%c", c); // Insert color specific drawing here.
  memcpy(_buffer + (FrameWidth* x + y), buff, StepSize);
}

// Private member function that uses threads to translate
// the contents of our proprietary storage to the actual
// canvas frame buffer.
void Frame::translateToCanvas() const
{
  for(int i = 0; i < FrameHeight; ++i)
    for(int j = 0; j < FrameWidth; ++j)
    {
      char buff[StepSize];
      memcpy(buff, &_buffer[(i * FrameWidth + j) * StepSize], StepSize);
      printf("\033[%d;%dH%s", PosY + i, PosX + j, buff);
    }
}

// Returns the ID of this frame.
int Frame::ID() const
{
  return _id;
}
