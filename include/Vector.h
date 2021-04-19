#ifndef LINEDRAW_VECTOR_H
#define LINEDRAW_VECTOR_H

typedef struct vector {
  float x, y;
} Vector;

Vector V_new(float x, float y);
void V_show(Vector v, char *label);
Vector V_diff(Vector v1, Vector v2);
Vector V_mult(Vector v, float k);
float V_dotProduct(Vector v1, Vector v2);
float V_magnitude(Vector v);
float V_PtPtDistance(Vector A, Vector P);
Vector V_unit(Vector v);
float V_PtLineDistance(Vector A, Vector B, Vector P);
int V_PtRegion(Vector P, Vector A, Vector B);
float V_PtSegmentDistance(Vector P, Vector A, Vector B);
Vector V_createMedium(Vector a, Vector b);
Vector V_shiftCoordinates(Vector v, float x, float y);
#endif // LINEDRAW_VECTOR_H
