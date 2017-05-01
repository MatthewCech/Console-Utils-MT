#include <stdio.h>
#include <cstdlib>
#include <string>
#include <cstring> // memcpy

#include "Canvas.hpp"

int main(int argc, char const *argv[])
{
  Canvas canvas(80,10);


  canvas.SetChar(0, 0, '0');
  canvas.SetColor(0, 0, {5,0,0});

  canvas.SetChar(3, 3, '3');
  canvas.SetColor(3, 3, {0,5,5});

  canvas.SetChar(5, 5, '5');
  canvas.SetColor(5, 5, {0,5,0});

  //printf("%s\n", canvas.GetBuffer());
  printf("\033[0;0H%s", canvas.GetBuffer());
  
  fflush(stdout);
  return 0;
}
