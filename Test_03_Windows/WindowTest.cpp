#include <iostream>
#include <unordered_map>
#include <vector>
#include <memory>
#include <stdio.h>
#include <string.h>

// Forward Declarations
class FrameManager;
class Frame;
const char example[] = "\033[22;30ma";
const int StepSize = sizeof(example) / sizeof(example[0]);

  /////////////////
 // Frame class //
/////////////////
class Frame
{
  friend FrameManager;
public:
  // Functions;
  void Write(unsigned char c, int x, int y);
  void Draw() const;
  int ID() const;

  // Variables
  int PosX;
  int PosY;
  int FrameWidth;
  int FrameHeight;

private:
  Frame(int id, int x, int y, int width, int height);
  const int _id;
  const int _bufferSize;
  char *_buffer;
  // Some form of buffer here storing draw information. 
};

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

void Frame::Write(unsigned char c, int x, int y)
{
  char buff[StepSize];
  sprintf(buff, "\033[22;31H%c", c); // Insert color specific drawing here.
  memcpy(_buffer + (FrameWidth* x + y), buff, StepSize);
}
void Frame::Draw() const
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









  ////////////////////////
 // FrameManager class //
////////////////////////
class FrameManager
{
public:
  FrameManager();
  Frame *GetFrame(int id);
  Frame *CreateFrame(int x, int y, int width, int height);
  void DrawAll() const;

private:
  std::unordered_map<int, Frame *> _frames; //maps IDs to frames.  
  int _next_id;
};

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
    iter.second->Draw();
}







  //////////
 // Main //
//////////
int main(int argc, char** argv)
{
  FrameManager manager;
  
  for(int i = 0; i < 10; ++i)
    manager.CreateFrame(20*i, 4*i, 10, 20);
  
  while(1)
    manager.DrawAll();

  return 0;
}