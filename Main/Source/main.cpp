#include "Testing/test_singleThread.hpp"


int main(int argc, char** argv)
{
  UNUSED(argc);
  UNUSED(argv);

  printf("\033[2J");
  printf("\033[?25l");
  DoSinglethreadTest();
  printf("\033[?25h");

  return 0;
}
