#include "Testing/test_multiThread.hpp"
#include <string>

int main(int argc, char** argv)
{
  int threadCount = 4;
  if(argc > 1)
    threadCount = atoi(argv[1]);

  printf("\033[2J");
  printf("\033[?25l");
  DoMultiThreadTest(threadCount);
  printf("\033[?25h");

  return 0;
}
