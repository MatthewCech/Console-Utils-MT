#include "FrameManager.hpp"

struct Thread_FrameData_Info
{
  int ThreadID;
  FrameManager *Manager; 
};

void Thread_FrameData_Main(Thread_FrameData_Info info);
