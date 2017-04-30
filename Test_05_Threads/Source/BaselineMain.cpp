
#include <cstdlib> // atoi
#include "ConsoleTest/MainTest.hpp"


int main(int argc, char* argv[])
{
  int threadCount = 4;

  if(argc > 1)
    threadCount = std::atoi(argv[1]);

  return RunTest(threadCount);
}
