#pragma once

#include "FrameManager.hpp"
#include "RGBColor.hpp"
#include "utilities.hpp"
#include <string.h>
#include <string>
#include <chrono>
// rand
#include <cstdlib>
#include <stdlib.h>

// Testing window creation
Frame* makeTestWindow(FrameManager &manager, int x, int y, int index)
{
  // Colors
  const RGBColor Something{ 2, 1, 4};
  const RGBColor Black{ 0,0,0};
  const RGBColor Gray {1,1,1};
  const RGBColor Ice{ 4,4,5};

  int id = manager.CreateFrame(x, y, 30, 10, index)->ID();
  Frame *frame = manager.GetFrame(id);
  const char *buf = "Hello World!";
  const char *buf2 = "This is a test.";
  std::string buf3 = std::string("We're on layer ") + std::to_string(index);
  frame->AddBorder(Ice, Gray);
  frame->Write(buf, strlen(buf), 1, 2, Something);
  frame->Write(buf2, strlen(buf2), 1, 4, Something);
  frame->Write(buf3.c_str(), strlen(buf3.c_str()), 1, 5, Something);
  return frame;
}
