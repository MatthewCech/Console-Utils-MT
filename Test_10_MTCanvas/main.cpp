#include <stdio.h>
#include <cstdlib>
#include <string>
#include <cstring> // memcpy
#include <iostream>

#include "Canvas.hpp"

int main(int argc, char const *argv[])
{
  Canvas canvas; // constructed with default size
  canvas.UpdateBufferSize(10,10);

  canvas.SetColorMany(0,0, -1, {-1}, {1,2,0});

  std::string blah = "THIS IS A VERY LONaasdfasdfjasdfkjahsdlkfjhasdlkfjhaksjldhflakjshdflkajhsdflkahjsdflkjashdflkajshdflkjashdflkajshdflkashfkjhaG STRING!";

  canvas.SetString(60, 8, blah.c_str());
  canvas.SetColorMany(60, 8, blah.size(), {-1}, {5,0,0});


  try {
    canvas.SetChar(150, 1, 1);
  } catch(CanvasBoundException &er) {
    std::cout << "ERROR WITH 15,1: " << er.what() << std::endl;
  }

  try {
    canvas.SetChar(1,150, 1);
  } catch(CanvasBoundException &er) {
    std::cout << "ERROR WITH 1,15: " << er.what() << std::endl;
  }

  try {
    canvas.SetChar(150,150, 1);
  } catch(CanvasBoundException &er) {
    std::cout << "ERROR WITH 15,15: " << er.what() << std::endl;
  }


  //printf("%s\n", canvas.GetBuffer());
  printf("\033[0;0H%s", canvas.GetBuffer());
  
  fflush(stdout);
  return 0;
}
