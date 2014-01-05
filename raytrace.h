#ifndef RAYTRACE_H
#define RAYTRACE_H
#include "linearalgebra.h"
/*
Simple raytracer.

Geoffrey Matthews
2014
*/

typedef struct ray {
  vector position;
  vector direction;
} *ray;

ray rayMalloc(void);
void rayFree(ray r);
ray makeRay(double x, double y, double z,
	    double u, double v, double w);

typedef struct sphere {
  vector center;
  double radius;
  vector color;
} *sphere;

sphere sphereMalloc(void);
void sphereFree(sphere s);
sphere makeSphere(double x, double y, double z,
		  double radius,
		  double r, double g, double b);
void sphereCopy(sphere s1, sphere s2);

#define MAXOBJECTS 500

typedef sphere objectArray[MAXOBJECTS];

typedef struct world {
  vector eye;
  vector light;
  objectArray objects;
  int length;
  vector backgroundColor;
} *world;

world worldMalloc(void);
void worldFree(world w);

void addSphere(world w, sphere  s);

void quadratic(double a, double b, double c,
	       int* n,
	       double* s1, double* s2);
  
void sphereNormal(sphere  s,
		  vector pos,
		  vector norm);
  
void tracer(const char* filename,
	    int resolution,
	    world  world);
  
void colorAt(double x, double y,
	     world  world,
	     vector color);

void sendRay(ray  ray,
	     world  world,
	     vector color);

void lambert(sphere  sphere,
	     vector pos,
	     world  world,
	     vector color);

void firstHit(ray  ray,
	      world  world,
	      int* success,
	      vector pos,
	      sphere sphere);

void intersect(sphere  sphere,
	       ray  ray,
	       int* success,
	       vector pos);

#endif
  
