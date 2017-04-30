#pragma once

#include "common_defines.hpp"

// String manupulation
#include <string>
#include <iomanip>  
#include <sstream>
#include <iostream>
#include <cstdio>

// Timing
#include <chrono>
#include <numeric>
#include <functional>

// Threadding
#include <thread>
#include <atomic>

// Containers
#include <vector>

  /////////////////
 // OS Specific //
/////////////////
#ifdef _WIN32
  // Windows
  #include <windows.h>
#else 
  // *Nix specifically
  #include <sys/ioctl.h>
  #include <stdio.h>
  #include <unistd.h>
#endif

  ////////////
 // Colors //
////////////
#include "ConsoleDraw/colors.hpp"

  ///////////////////////
 // Drawing Interface //
///////////////////////
#include "ConsoleDraw/interface.hpp"
