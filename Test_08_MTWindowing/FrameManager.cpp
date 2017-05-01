#include "FrameManager.hpp"
#include <stdio.h>
#include <memory>
#include <cstring>


// Default ctor, initializes with no frames.
FrameManager::FrameManager() 
 : _frames()
 , _next_id(0)
{  }

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

  // Make and return new frame.
  Frame *f = new Frame(id, x, y, width, height, layer);
  _frames[id] = f;
  return f;
}

// Draws all frames to the canvas.
void FrameManager::Update()
{
  for(auto &iter : _frames)
  {
    Frame *f = iter.second;
    char *arr = new char[f->_width + 1];

    // For all rows,
    for(int i = 0; i < f->_height; ++i)
    {
      // Copy in the memory in the buffer and set our terminator
      memcpy(arr, &(f->_bufferChar[i * f->_width]), f->_width);
      arr[f->_width] = '\0';

      // Print line out
      printf("\033[%d;%dH%s", f->_posY + i, f->_posX, arr);
    }

    delete arr;
  }
}

// Deletes then erases ID internally.
void FrameManager::DeleteFrame(int id)
{
  if(_frames.find(id) != _frames.end())
  {
    delete _frames[id];
    _frames.erase(id);
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
  
}