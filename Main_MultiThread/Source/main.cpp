#include "GlobalData.hpp"         // gives us 'Globals' object
#include "ConsoleSizeHandler.hpp" // captures window size and stores in globals
#include "SigHandler.hpp"         // allows us to handle sigterms

#include "Testing/test_multiThread.hpp"
#include <string>

#define SIZE_CHECK_FREQUENCY 100

int main(int argc, char** argv)
{
  Globals.threadsCanRun = true;
  Globals.sizeHandler = std::thread(Thread_CaptureConsoleSize, SIZE_CHECK_FREQUENCY);

  InitSigHandler();

  int threadCount = 4;
  if(argc > 1)
    threadCount = atoi(argv[1]);

  printf("\033[2J");
  printf("\033[?25l");
  DoMultiThreadTest(threadCount);

  // In case we do ever leave the test loop
  Globals.threadsCanRun = false;

  return 0;
}
