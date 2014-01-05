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
void assign(vector v, double x, double y, double z);
void copy(vector v1, vector v2);
void add(vector v1, vector v2, vector v3);
void subtract(vector v1, vector v2, vector v3);
void multiply(vector v, double s);
double dot(vector v1, vector v2);
double mag(vector v);
void normalize(vector v);
double distance(vector p1, vector p2);
void vectorPrint(vector v);
void vectorIntegerPrintf(FILE *file, vector color);
#endif
