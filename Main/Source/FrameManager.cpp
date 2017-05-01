#include "FrameManager.hpp"
#include <stdio.h>
#include <memory>
#include <cstring>

// *Nix specifically
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>

// Default ctor, initializes with no frames.
// you probably do NOT want to set adjustment values at all in 
// any production code.
FrameManager::FrameManager(int adjustmentX, int adjustmentY)
 : _frames()
 , _bufferSize(0)
 , _next_id(1)
 , _width(0)
 , _height(0)
 , _adjustmentX(adjustmentX)
 , _adjustmentY(adjustmentY)
 , _ordering(nullptr)
 , _canvas()
{
  updateDimensions();
  _canvas.UpdateBufferSize(_width + 1, _height);
  initOrderingBuffer();
}

// Destructor, cleans all frames up.
FrameManager::~FrameManager()
{
  for(auto &iter : _frames)
    delete iter.second;
}

// Gets and returns frame with id arg1. 
// If frame does not exist, returns nullptr.
Frame *FrameManager::GetFrame(int id)
{
  if(_frames.find(id) == _frames.end())
    return nullptr;
  return _frames[id];
}

// Creates and returns a new frame at position <x>,<y> with the 
// size <width> x <height>. The higher the layer, the more in-front
// the frame will draw. Default is 0. 
Frame *FrameManager::CreateFrame(int x, int y, int width, int height, int layer)
{
  // Generate ID for frame, verify availability.
  int id = _next_id++;
  if(_frames.find(id) != _frames.end())
    throw "Duplicate Frame ID for this manager! This shouldn't be possible!";

  // Make and return new frame. Update ordering buffer.
  Frame *f = new Frame(id, this, x, y, width, height, layer);
  _frames[id] = f;
  updateOrderingBuffer();
  return f;
}

// Draws all frames to the canvas.
void FrameManager::Update()
{
  if(updateDimensions())
  {
    initOrderingBuffer();
    updateOrderingBuffer();
    _canvas.UpdateBufferSize(_width, _height);
  }

  for(auto &iter : _frames)
  {
    const Frame *f = iter.second;
    const int id = f->ID();
    const int startX = f->PosX();
    const int startY = f->PosY();
    const int width = f->Width();
    const int height = f->Height();

    for(int x = 0; x < width; ++x)
      for(int y = 0; y < height; ++y)
      {
        const int pos = (startY + y) * _width + (startX + x); 
        if(pos > _bufferSize - 1)
          continue;
        if(_ordering[pos].ID == id)
        {
          const int xf = startX + x;
          const int yf = startY + y;
          const int posf = y * f->_width + x;
          //if(xf > _width - 1)
          //  continue;
          //if(yf > _height - 1)
           // continue;
          _canvas.SetChar(xf, yf, f->_bufferChar[posf]);
          _canvas.SetColor(xf, yf, f->_bufferAttributes[posf].Foreground ,f->_bufferAttributes[posf].Background);
        }
      }
  }
  //_canvas.SetColorMany(0, 0, -1, { -1 }, { 5,0,0});
  printf("\033[0;0H%s", _canvas.GetBuffer());
  _canvas.ResetBuffer();
}

// Deletes then erases ID internally.
void FrameManager::DeleteFrame(int id)
{
  if(_frames.find(id) != _frames.end())
  {
    delete _frames[id];
    _frames.erase(id);
    updateOrderingBuffer();
  }
}

int FrameManager::ScreenWidth() const
{
  return _width;
}
int FrameManager::ScreenHeight() const
{
  return _height;
}
int FrameManager::GetFrameCount() const
{
  return _frames.size();
}

// Returns if _width and _height were updated
bool FrameManager::updateDimensions()
{
  struct winsize screenSize;
  ioctl(STDOUT_FILENO,TIOCGWINSZ,&screenSize);
  int height = screenSize.ws_row + _adjustmentY;
  int width = screenSize.ws_col + _adjustmentX;

  if(height != _height || _width != width)
  {
    _width = width;
    _height = height;
    _bufferSize = width * height;
    return true;
  }

  return false;
}

void FrameManager::updateOrderingBuffer()
{
  memset(_ordering, 0, _bufferSize * sizeof(LayerInfo));
  for(auto &iter : _frames)
  {
    const Frame *f = iter.second;
    const int id = f->ID();
    const int layer = f->Layer();
    const int startX = f->PosX();
    const int startY = f->PosY();

    for(int x = 0; x < f->_width; ++x)
      for(int y = 0; y < f->_height; ++y)
      {
        const int pos = (startY + y) * _width + (startX + x); 
        if(startX + x > _width - 1)
          continue;
        if(startY + y > _height - 1)
          continue;
        if(pos > _bufferSize - 1 || pos < 0)
          continue;

        if(_ordering[pos].ID == 0) // If no ID has been assigned, we're in!
          _ordering[pos] = LayerInfo(id, layer);
        else if(_ordering[pos].Layer < layer)
           _ordering[pos] = LayerInfo(id, layer);
      }
  }
}

void FrameManager::initOrderingBuffer()
{
  if(_ordering)
    delete[] _ordering;

  _ordering = new LayerInfo[_bufferSize];
  memset(_ordering, 0, _bufferSize * sizeof(LayerInfo));
}
