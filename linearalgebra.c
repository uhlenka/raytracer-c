#include <stdio.h>   /* printf */
#include <stdlib.h>  /* malloc */
#include <math.h>    /* sqrt   */
#include "linearalgebra.h"

vector vectorMalloc(void) {
  vector v = (vector)malloc(sizeof(struct vector));
  if (v == NULL) {
    printf("ERROR in vectorMalloc.\n");
    exit(-1);
  }
  v->x = 0.0; v->y = 0.0; v->z = 0.0;
  return v;
}

void vectorFree(vector v) {
  free(v);
}

void assign(vector v, double x, double y, double z) {
  *v = (struct vector){x,y,z};
}

void copy(vector v1, vector v2) {
  v1->x = v2->x; v1->y = v2->y; v1->z = v2->z;
}

void add(vector v1, vector v2, vector v3) {
    v3->x = v1->x + v2->x;
    v3->y = v1->y + v2->y;
    v3->z = v1->z + v2->z;
  }

void subtract(vector v1, vector v2, vector v3) {
  v3->x = v1->x - v2->x;
  v3->y = v1->y - v2->y;
  v3->z = v1->z - v2->z;
}

void multiply(vector v, double s) {
  v->x *= s;
  v->y *= s;
  v->z *= s;
}

double dot(vector v1, vector v2) {
  return v1->x*v2->x + v1->y*v2->y + v1->z*v2->z;
}

double mag(vector v) {
  return sqrt(dot(v, v));
}

void normalize(vector v) {
  multiply(v, 1.0/mag(v));
}

double distance(vector p1, vector p2) {
  vector v = vectorMalloc();
  subtract(p1, p2, v);
  return mag(v);
}

void vectorPrint(vector v) {
  printf("vector(%0.2f, %0.2f, %0.2f)", v->x, v->y, v->z);
}

void vectorIntegerPrintf(FILE *file, vector color) {
  fprintf(file, "%d %d %d\n", (int)color->x, (int)color->y, (int)color->z);
}


