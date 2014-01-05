#ifndef VECTORS_H
#define VECTORS_H
/*
A simple package to support vector 
operations needed for a ray tracer.

Geoffrey Matthews
2014
*/

typedef struct vector{
  double x;
  double y;
  double z;
} *vector;

vector vectorMalloc(void);
void vectorFree(vector v);
void assign(vector target, double x, double y, double z);
void copy(vector target, vector source);
void add(vector target, vector source1, vector source2);
void subtract(vector target, vector source1, vector source2);
void multiply(vector target, double s);
double dot(vector v1, vector v2);
double mag(vector v);
void normalize(vector v);
double distance(vector p1, vector p2);
void vectorPrint(vector v);
void vectorIntegerPrintf(FILE *file, vector color);
#endif
