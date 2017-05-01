#include "Thread_FrameData.hpp"
#include <string>


void Thread_FrameData_Main(Thread_FrameData_Info info)
{
  printf("Hello from thread %d!\n", info.ThreadID);
  int timeout = 500000;
  while(timeout-->0)
  {
    info.Manager->Thread_WaitYourTurn();
    Frame *f = info.Manager->Thread_GetNextFrame();
    std::string buf = std::string("Drawn by thread ") + std::to_string(info.ThreadID);
    f->Write(buf.c_str(), buf.size(), 1, 1, {4,5,2});
    if(f != nullptr)
      info.Manager->Thread_UpdateFrame(f);
  }
}
