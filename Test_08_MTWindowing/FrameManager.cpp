#include "FrameManager.hpp"



// Default ctor, initializes with no frames.
FrameManager::FrameManager() 
 : _next_id(0)
 , _frames()
{  }

// Gets and returns frame with id arg1. 
// If frame does not exist, returns nullptr.
Frame *FrameManager::GetFrame(int id)
{
  if(_frames.find(id) == _frames.end())
    return nullptr;
  return _frames[id];
}

// Creates and returns a new frame at position arg1,arg2 with the size arg3,arg4.
Frame *FrameManager::CreateFrame(int x, int y, int width, int height)
{
  // Generate ID for frame, verify availability.
  int id = _next_id++;
  if(_frames.find(id) != _frames.end())
    throw "Duplicate Frame ID for this manager! This shouldn't be possible!";

  // Make and return new frame.
  Frame *f = new Frame(id, x, y, width, height);
  _frames[id] = f;
  return f;
}

void FrameManager::DrawAll() const
{
  for(auto &iter : _frames)
    iter.second->translateToCanvas();
}
