///////////////////////////////////////////////////////////
// Handles all creation and destruction of frame objects,
// and hides all of the threading from the user.
///////////////////////////////////////////////////////////
#pragma once
#include "Frame.hpp"
#include <unordered_map>


class FrameManager
{
public:
  // Constructor
  FrameManager();
  ~FrameManager();
  Frame *CreateFrame(int x, int y, int width, int height, int layer = 0);
  Frame *GetFrame(int id);
  void DeleteFrame(int id);
  void Update();

  // Information
  int ScreenWidth() const;
  int ScreenHeight() const;
  int GetFrameCount() const;

private:
  // Variables
  void updateSize();
  std::unordered_map<int, Frame *> _frames; //maps IDs to frames.  
  int *_order;
  int _next_id;
  int _width;
  int _height;
};
