#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>


#include <chrono>
#include <thread>

#define Delay_Check 100
#define Delay_Main 10

struct Globals
{
  std::thread t_timeCheck;
  bool threadsShouldRun;
};

Globals globals;

void DoTimeCheck(struct winsize *cur, int delay)
{
  while(globals.threadsShouldRun)
  {
    ioctl(STDOUT_FILENO, TIOCGWINSZ, cur);
    std::this_thread::sleep_for (std::chrono::milliseconds(delay));
  }
}

void handle_exit(int s)
{
  globals.threadsShouldRun = false;

  if(globals.t_timeCheck.joinable())
    globals.t_timeCheck.join();

  printf("\nSHUTTING DOWN!\n");
  std::this_thread::sleep_for (std::chrono::milliseconds(500));
  printf("DONE!\n");
  exit(1); 
}

int main (int argc, char **argv)
{
  globals.threadsShouldRun = true;

  {
    struct sigaction sigIntHandler;
    sigIntHandler.sa_handler = handle_exit;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;
    sigaction(SIGINT, &sigIntHandler, NULL);
  }
  

  struct winsize prev = {0};
  struct winsize cur = {0};

  globals.t_timeCheck = std::thread(DoTimeCheck, &cur, Delay_Check);

  while(true)
  {
    if(cur.ws_row != prev.ws_row || cur.ws_col != prev.ws_col)
    {
      prev = cur;
      printf("\nWINDOW SIZE CHANGED: %d by %d\n", prev.ws_row, prev.ws_col);
    }
    else
    {
      printf(".");
      fflush(stdout);
    }
    std::this_thread::sleep_for (std::chrono::milliseconds(Delay_Main));
  }

  return 0;
}
