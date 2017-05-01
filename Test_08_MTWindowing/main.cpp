#include "FrameManager.hpp"
#include "Color.hpp"
#include <string.h>


int main(int argc, char** argv)
{
  FrameManager manager;
  int id = manager.CreateFrame(10, 3, 30, 10, 1)->ID();
  Frame *frame = manager.GetFrame(id);
  frame->Write("Hello World!", strlen("Hello World!"), 0, 0);
  while(1)
    manager.Update();

  return 0;
}