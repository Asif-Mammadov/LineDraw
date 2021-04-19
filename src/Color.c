#include "../include/Color.h"

//-------------------------------
// a : integer
// function makes 0 < a < 255
int _adjustValue(int a) {
  if (a > 255)
    return 255;
  else if (a < 0)
    return 0;
  return a;
}
//-----------------------------------------------------------------
// r, g, b : integers representing RGB color model respectively
// precondition : r, g and b must be bigger than 0 and less than 255,
// otherwise the value will be adjusted to its maximum or minimum
// return value : new struct color with (r, g, b)
Color C_new(int r, int g, int b) {
  Color tmp = {_adjustValue(r), _adjustValue(g), _adjustValue(b)};
  return tmp;
}
