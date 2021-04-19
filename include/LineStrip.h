#include "VertexNode.h"
#ifndef LINEDRAW_LINESTRIP_H
#define LINEDRAW_LINESTRIP_H

typedef struct linestrip {
  VertexNode *VHead;
  VertexNode *VCurrent;
  int VertexNum;
  char chosen;
} LineStrip;

LineStrip *LN_new();
#endif