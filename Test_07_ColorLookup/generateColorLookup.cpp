// Generate a header file for super fast lookup of a char number as a string

#include <stdio.h>

int main(int argc, char const *argv[])
{
  printf("// THIS FILE WAS AUTOMATICALLY GENERATED BY generateColorLookup.cpp\n");
  printf("#pragma once\n\n");
  printf("const char ColorCodeLookup[][] = {\n");

  for(int i = 0; i < 256; ++i)
    printf("\"%03d\", ", i);

  printf("\n};\n");

  return 0;
}