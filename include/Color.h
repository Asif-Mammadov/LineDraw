#ifndef LINEDRAW_COLOR_H
#define LINEDRAW_COLOR_H

typedef struct color {
  int r, g, b;
} Color;

Color C_new(int r, int g, int b);
#endif