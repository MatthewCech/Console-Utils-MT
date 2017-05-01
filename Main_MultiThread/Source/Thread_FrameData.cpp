#include "Thread_FrameData.hpp"



void Thread_FrameData_Main(Thread_FrameData_Info info)
{
  printf("Hello from thread %d!\n", info.ThreadID);
}
