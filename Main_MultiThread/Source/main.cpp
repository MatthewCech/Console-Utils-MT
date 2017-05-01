#include "GlobalData.hpp"         // gives us 'Globals' object
#include "ConsoleSizeHandler.hpp" // captures window size and stores in globals
#include "SigHandler.hpp"         // allows us to handle sigterms

#include "Testing/test_multiThread.hpp"
#include <string>
#include <algorithm> //std::transform

#define SIZE_CHECK_FREQUENCY 100

int main(int argc, char** argv)
{
  int threadCount = 4;
  if(argc > 1)
    threadCount = atoi(argv[1]);

  int windowCount = 6;
  if(argc > 2)
    windowCount = atoi(argv[2]);

  Globals.ThreadDebug = false;
  if(argc > 3)
  {
    std::string arg = argv[3];
    std::transform(arg .begin(), arg .end(), arg .begin(), ::tolower);

    if(arg == "true" || arg == "t" || std::atoi(arg.c_str()) == 1)
      Globals.ThreadDebug = true;
  }

  Globals.Loops = 0;
  Globals.Time = 0;

  Globals.threadsCanRun = true;
  Globals.sizeHandler = std::thread(Thread_CaptureConsoleSize, SIZE_CHECK_FREQUENCY);

  InitSigHandler();


  printf("\033[2J");
  printf("\033[?25l");
  DoMultiThreadTest(threadCount, windowCount);

  // In case we do ever leave the test loop
  Globals.threadsCanRun = false;

  printf("\033[?25h"); // Show the cursor again
  std::this_thread::sleep_for (std::chrono::milliseconds(THREAD_WAIT));
  printf("\n\033[0m"); // Clears color  
  printf("\033[H");    // Reposition cursor in top-left
  printf("\033[2J");   // Clears the screen


  return 0;
}
