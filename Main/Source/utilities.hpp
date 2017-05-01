#pragma once

#define UNUSED(x) (void)(x)

inline int posMod(int val, int max)
{
  val = (val%max);
  if(val < 0) val+=max;
  return val;
}
