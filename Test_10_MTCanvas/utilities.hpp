#pragma once

inline int posMod(int val, int max)
{
  val = (val%max);
  if(val < 0) val+=max;
  return val;
}
