#pragma once

#include "utilities.hpp"
#include "GlobalData.hpp"

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>

#include <chrono>
#include <thread>

#define THREAD_WAIT 30
#define NOTICE_WAIT 300

void HandleSig(int s)
{
  UNUSED(s);

  printf("\033[?25h");     // Show the cursor again

  Globals.threadsCanRun = false;

  Globals.sizeHandler.join();

  // wait for threads to catch up
  std::this_thread::sleep_for (std::chrono::milliseconds(THREAD_WAIT));
  
  int width  = Globals.width;
  int height = Globals.height;

  printf("\033[0m");  
  printf("\n\033[%d;%dH\033[48;05;166m                                     ", height/2 -2, width/2 - 18);         
  printf("\n\033[%d;%dH\033[48;05;166m \033[0m                                   \033[48;05;166m ", height/2 -1, width/2 - 18);
  printf("\n\033[%d;%dH\033[48;05;166m \033[0m       DEMO IS SHUTTING DOWN...    \033[48;05;166m ", height/2   , width/2 - 18);
  printf("\n\033[%d;%dH\033[48;05;166m \033[0m                                   \033[48;05;166m ", height/2 +1, width/2 - 18);
  printf("\n\033[%d;%dH\033[48;05;166m                                     ", height/2 +2, width/2 - 18);
  printf("\n\033[0m"); // Clears color  

  printf("\033[H"); // Reposition cursor in top-left
  std::this_thread::sleep_for (std::chrono::milliseconds(NOTICE_WAIT));

  printf("\033[2J"); // Clears the screen

  exit(1); 
}

void InitSigHandler()
{
  struct sigaction sigIntHandler;
  sigIntHandler.sa_handler = HandleSig;
  sigemptyset(&sigIntHandler.sa_mask);
  sigIntHandler.sa_flags = 0;
  sigaction(SIGINT, &sigIntHandler, NULL);
}

