#include <stdio.h>
#include <cstdlib>
#include <string>
#include <cstring> // memcpy

#include "Canvas.hpp"

int main(int argc, char const *argv[])
{
  Canvas canvas(2,2);

  canvas.SetChar(0, 0, '@');
  //canvas.SetChar(3, 3, 'A');
  canvas.SetColor(0, 0, {5,0,0}, {0,2,0});

  //printf("\033[0;0H%s\n", canvas.GetBuffer());
  
  printf("%s\n", canvas.GetBuffer());
  fflush(stdout);

  return 0;
}
