///////////////////////////////////////////////////////////
// Handles all creation and destruction of frame objects,
// and hides all of the threading from the user.
///////////////////////////////////////////////////////////
#include "Frame.hpp"
#include <unordered_map>


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
