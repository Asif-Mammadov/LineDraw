#include "../include/LineStrip.h"
#include <stdlib.h>

// function creates new LineStrip
// return value : pointer to a new LineStrip
LineStrip *LN_new() {
  LineStrip *tmp = (LineStrip *)malloc(sizeof(LineStrip));
  tmp->VCurrent = NULL;
  tmp->VHead = NULL;
  tmp->VertexNum = 0;
  tmp->chosen = 'v';
  return tmp;
}