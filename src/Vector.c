#include "../include/Vector.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

//------------------------------------------------------
// x : a float representing value of a vector on x-axis.
// y : a float representing value of a vector on y-axis.
// return value: a vector with (x, y) coordinates
Vector V_new(float x, float y) {
  Vector tmp;
  tmp.x = x;
  tmp.y = y;
  return tmp;
}

//---------------------------------------------------
// v : vector that we need to display.
// label : name of a vector.
// return value : none
// function prints name and coordinates of v
void V_show(Vector v, char *label) {
  printf("%-5s: (%.2f, %.2f)\n", label, v.x, v.y);
}

//----------------------------------------------------
// v1 and v2 : vectors
// return value : new vector which is v1 - v2
Vector V_diff(Vector v1, Vector v2) { return V_new(v1.x - v2.x, v1.y - v2.y); }

//---------------------------------------------------------------------------------------
// v : vector
// k : float coefficient to multiply.
// return value : new vector which is k * v
Vector V_mult(Vector v, float k) { return V_new(k * v.x, k * v.y); }

//----------------------------------------------------------------
// v1 and v2 : vectors
// return value : float representing dot product of v1 and v2
float V_dotProduct(Vector v1, Vector v2) { return v1.x * v2.x + v1.y * v2.y; }

//-------------------------------------------------
// v : vector
// return value: float representing magnitude of v
float V_magnitude(Vector v) { return sqrt(V_dotProduct(v, v)); }

//-----------------------------------------------------------
// A and P : vectors
// return value : float representing distance between A and P
float V_PtPtDistance(Vector A, Vector P) {
  Vector AP = V_diff(P, A);
  return V_magnitude(AP);
}

//-------------------------------------------------------------------------------
// v : vector
// Precondition: v should not be (0, 0). In that case function returns (1, 0)
// return value : new vector w parallel to v and magnitude of 1
// which means that w = kv and ||w|| = 1
Vector V_unit(Vector v) {
  if (v.x == 0 && v.y == 0) {
    printf("<WARNING> Your vector is (0, 0)\nReturned (1, 0)\n");
    return V_new(1, 0);
  }
  float magnitude = V_magnitude(v);
  return V_new(v.x / magnitude, v.y / magnitude);
}

//-----------------------------------------------------------------
// P : vector considered as a point
// A and B : vectors and points on line AB
// Precondition : Vector AB (V_diff(B, A)) should not be (0, 0)
// return value : float representing the distance between P and AB
//
//           P
//          /|
//         / |
//        /  |
//       /   |
//      /    |
//   A /_ _ _|_ _ _ B
//           D
//
float V_PtLineDistance(Vector P, Vector A, Vector B) {
  Vector AP = V_diff(P, A);
  Vector AB = V_diff(B, A);
  float magnitudeAB = V_magnitude(AB);
  if (magnitudeAB == 0) {
    printf(
        "ERROR\nV_PtLineDistance(): Magnitude AB is (0, 0). \nTerminating...");
  }
  Vector AD = V_mult(AB, V_dotProduct(AP, AB) / pow(magnitudeAB, 2));
  Vector PD = V_diff(AP, AD);
  return V_magnitude(PD);
}

//------------------------------------------------------------------------------------
// P : vector representing a point
// A and B : vectors representing extreme points of segment AB
// return value : integer representing to which region point P belongs to (1, 2
// or 3)
//
//        |   P    |
//        |        |
//     1  |    2   |   3
//        |        |
// __ __ _|__ __ __|__ __ __
//        A        B
//     1  |    2   |   3
//        |        |
//
int V_PtRegion(Vector P, Vector A, Vector B) {
  Vector AB = V_diff(B, A);
  Vector BA = V_diff(A, B);
  Vector AP = V_diff(P, A);
  Vector BP = V_diff(P, B);
  if ((V_dotProduct(AB, AP) >= 0) && (V_dotProduct(BA, BP) >= 0))
    return 2;
  else if ((V_dotProduct(AB, AP) < 0) && (V_dotProduct(BA, BP) > 0))
    return 1;
  else if ((V_dotProduct(AB, AP) > 0) && (V_dotProduct(BA, BP) < 0))
    return 3;
  else {
    printf("ERROR\nV_PtRegion(): Something went wrong\n"); // in case of a bug
    printf("AB = (%f, %f)\n", AB.x, AB.y);
    printf("AP = (%f, %f)\n", AP.x, AP.y);
    printf("BA = (%f, %f)\n", BA.x, BA.y);
    printf("BP = (%f, %f)\n", BP.x, BP.y);
    printf("Terminating...\n");
    exit(0);
  }
}

//--------------------------------------------------------------------------------
// P : vector representing a point
// A and B : vectors representing extreme points of segment AB
// return value : float which is a distance between point P and segment AB
//
//        |   P    |
//        |        |
//     1  |    2   |   3
//        |        |
// __ __ _|__ __ __|__ __ __
//        A        B
//     1  |    2   |   3
//        |        |
//
float V_PtSegmentDistance(Vector P, Vector A, Vector B) {
  int value = V_PtRegion(P, A, B);
  if (value == 2)
    return V_PtLineDistance(P, A, B);
  else if (value == 1)
    return V_PtPtDistance(P, A);
  else if (value == 3)
    return V_PtPtDistance(P, B);
  printf("ERROR\nV_PtSegmentDistance(): Something went "
         "wrong\nTerminating...\n"); // to report a bug
  exit(0);
}

//---------------------------------------------------------------
// A and B : Vectors
// return value : new vector which is in the middle of segment AB
Vector V_createMedium(Vector A, Vector B) {
  printf("(%f %f)\n", A.x, A.y);
  printf("(%f %f)\n", B.x, B.y);
  return V_new((A.x + B.x) / 2, (A.y + B.y) / 2);
}

//--------------------------------------------------------------------
// v : Vector
// x and y : float representing the length in x and y axis respectively
// return value : new Vector shifted by (x, y)
Vector V_shiftCoordinates(Vector v, float x, float y) {
  v = V_new(v.x + x, v.y + y);
  return v;
}