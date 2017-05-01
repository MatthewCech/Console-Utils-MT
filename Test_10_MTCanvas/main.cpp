#include <stdio.h>
#include <cstdlib>
#include <string>
#include <cstring> // memcpy

#include "Canvas.hpp"

int main(int argc, char const *argv[])
{
  Canvas canvas; // constructed with default size
  canvas.UpdateBufferSize(10,10);

  canvas.SetColorMany(0,0, -1, {-1}, {1,2,0});

  std::string blah = "THIS IS A VERY LONaasdfasdfjasdfkjahsdlkfjhasdlkfjhaksjldhflakjshdflkajhsdflkahjsdflkjashdflkajshdflkjashdflkajshdflkashfkjhaG STRING!";

  canvas.SetString(60, 8, blah.c_str());
  canvas.SetColorMany(60, 8, blah.size(), {-1}, {5,0,0});


  //printf("%s\n", canvas.GetBuffer());
  printf("\033[0;0H%s", canvas.GetBuffer());
  
  fflush(stdout);
  return 0;
}
