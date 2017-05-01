#include "FrameManager.hpp"
#include "Color.hpp"
#include <string.h>
#include <string>

// rand
#include <cstdlib>
#include <stdlib.h>

// Testing window creation
Frame* makeTestWindow(FrameManager &manager, int x, int y, int index)
{
  int id = manager.CreateFrame(x, y, 30, 10, index)->ID();
  Frame *frame = manager.GetFrame(id);
  const char *buf = "Hello World!";
  const char *buf2 = "This is a test.";
  std::string buf3 = std::string("Not to bad! L") + std::to_string(index);
  frame->AddBorder();
  frame->Write(buf, strlen(buf), 1, 2);
  frame->Write(buf2, strlen(buf2), 1, 4);
  frame->Write(buf3.c_str(), strlen(buf3.c_str()), 1, 5);
  return frame;
}

int main(int argc, char** argv)
{

  FrameManager manager;
  const int size = 3;
  Frame *f[size];
  const int countReset = 250;
  int count = countReset;


  for(int i = 0; i < size; ++i)
    f[i] = makeTestWindow(manager, rand() % manager.ScreenWidth(), rand() % manager.ScreenHeight(), i);
  //printf("here");
  //return 0;

  int max = 50000;
  int shuffle = 0;
  while(--max)
  {
    if(--count == 0)
    {
      ++shuffle;
      shuffle = shuffle % 3;
      int x = rand() % manager.ScreenWidth();
      int y = rand() % manager.ScreenHeight();
      f[shuffle]->SetLocation(x, y);
      count = countReset;
    }

    manager.Update();
  }

  return 0;
}