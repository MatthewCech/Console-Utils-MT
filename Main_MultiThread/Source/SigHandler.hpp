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

void HandleSig(int s)
{
  UNUSED(s);

  Globals.threadsCanRun = false;
  
  Globals.sizeHandler.join();

  // wait for threads to catch up
  std::this_thread::sleep_for (std::chrono::milliseconds(150));
  
  int width  = Globals.width;
  int height = Globals.height;

  printf("\033[0m");   
  printf("\n\033[%d;%dH\033[48;05;166m                                     ", height/2 -2, width/2 - 18);         
  printf("\n\033[%d;%dH\033[48;05;166m \033[0m                                   \033[48;05;166m ", height/2 -1, width/2 - 18);
  printf("\n\033[%d;%dH\033[48;05;166m \033[0m       DEMO IS SHUTTING DOWN...    \033[48;05;166m ", height/2   , width/2 - 18);
  printf("\n\033[%d;%dH\033[48;05;166m \033[0m                                   \033[48;05;166m ", height/2 +1, width/2 - 18);
  printf("\n\033[%d;%dH\033[48;05;166m                                     ", height/2 +2, width/2 - 18);
  printf("\n\033[0m");            

  printf("\033[H"); // reposition cursor in top-left
  std::this_thread::sleep_for (std::chrono::milliseconds(1100));

  printf("\033[2J"); // Clears the screen
  printf("\033[?25h");     // Show the cursor again
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

