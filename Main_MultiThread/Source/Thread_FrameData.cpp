#include "Thread_FrameData.hpp"
#include "GlobalData.hpp"

#include <string>


void Thread_FrameData_Main(Thread_FrameData_Info info)
{
  while(Globals.threadsCanRun)
  {
    info.Manager->Thread_WaitYourTurn();
    Frame *f = info.Manager->Thread_GetNextFrame();
    std::string buf = std::string("Drawn by thread ") + std::to_string(info.ThreadID);
    f->Write(buf.c_str(), buf.size(), 1, 1, {4,5,2});
    if(f != nullptr)
      info.Manager->Thread_UpdateFrame(f, info.ThreadID % 10);
  }
}
