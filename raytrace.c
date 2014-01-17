#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "raytrace.h"

/*ray rayMalloc(void) {
  ray r = (ray)malloc(sizeof(struct ray));
  //r->position = vectorMalloc();
    //vector pos;
    //assign(&pos, 0.0, 0.0, 0.0);
    //r->position = &pos;
    assign(&r->position, 0.0, 0.0, 0.0);
  //r->direction = vectorMalloc();
    //vector dir;
    //assign(&dir, 0.0, 0.0, 0.0);
    //r->direction = &dir;
    assign(&r->direction, 0.0, 0.0, 0.0);
  return r;
}
void rayFree(ray r) {
  //vectorFree(r->position);
  //vectorFree(r->direction);
  free(r);
}*/
ray makeRay(double x, double y, double z,
	    double u, double v, double w) {
  //ray r = rayMalloc();
    ray r;
  assign(&r.position, x,y,z);
  assign(&r.direction, u,v,w);
  return r;
}

/*sphere sphereMalloc(void) {
  sphere s  = (sphere)malloc(sizeof (struct sphere));
  //s->center = vectorMalloc();
    //vector center;
    //assign (&center, 0.0, 0.0, 0.0);
    //s->center = &center;
    assign(&s.center, 0.0, 0.0, 0.0);
  //s->color = vectorMalloc();
    //vector color;
    //s->color = &color;
  assign(&s.color, 0.5, 0.5, 0.5);
  s.radius = 1.0;
  return s;
}
void sphereFree(sphere s) {
  //vectorFree(s->center);
  //vectorFree(s->color);
  free(s);
}*/
sphere makeSphere(double x, double y, double z,
		  double radius,
		  double r, double g, double b) {
  //sphere s = sphereMalloc();
    sphere s;
  assign(&s.center, x,y,z);
  s.radius = radius;
  assign(&s.color, r,g,b);
  return s;
}

void sphereCopy(sphere *s1, sphere *s2) {
  copy(&s1->center, &s2->center);
  s1->radius = s2->radius;
  copy(&s1->color, &s2->color);
}

/*world worldMalloc(void) {
  world w = (world)malloc(sizeof(struct world));
  //w->eye = vectorMalloc();
    //vector eye;
    //w->eye = &eye;
  assign(&w.eye, 0.0, 0.0, 200.0);
  //w->light = vectorMalloc();
    //vector light;
    //w->light = &light;
  assign(&w.light, 1.0, 1.0, 1.0);
  normalize(&w.light);
  //w->backgroundColor = vectorMalloc();
    //vector bgc;
    //w->backgroundColor = &bgc;
  assign(&w.backgroundColor, 0.5, 0.75, 1.0);
  w.length = 0;
  return w;
}
void worldFree(world w) {
  //vectorFree(w->eye);
  //vectorFree(w->light);
  //vectorFree(w->backgroundColor);
  free(w);
}*/

void addSphere(world *w, /* inout */
	       sphere *s /* in */) {
/* add a sphere to the world */
  if (w->length >= MAXOBJECTS) {
    printf("WARNING: Too many objects in world, not adding new sphere.\n");
    return;
  }
  w->objects[w->length] = s;
  w->length += 1;
}

void quadratic(double a, double b, double c, /* in */
	       int* n,  /* out, the number of solutions */
	       double* s1, /* out, smallest solution */
	       double* s2  /* out, other solution */) {
  double discriminant, sqrtDiscriminant;
  discriminant = b*b - 4.0*a*c;
  if (discriminant < 0.0) {
    *n = 0;
  } else if (discriminant < 1.0e-10) {
    *n = 1;
    *s1 = -b/(2.0*a);
  } else {
    *n = 2;
    sqrtDiscriminant = sqrt(discriminant);
    *s1 = (-b - sqrtDiscriminant)/(2.0*a);
    *s2 = (-b + sqrtDiscriminant)/(2.0*a);
  }
}

void sphereNormal(sphere *s,    /* in */
		  vector *pos,  /* in */
		  vector *norm  /* out */) {
/* find the normal to a sphere s at position pos */
  subtract(norm, pos, &s->center);
  normalize(norm);
}

void tracer(const char* filename, /* file to write image into */
	    int resolution,       /* in, width and height, in 100 pixels */
	    world *theworld          /* in, world to render */){
/* raytrace the scene */
  FILE *file;
  double x, y, inc;
  int size, i, j;
  //vector color = vectorMalloc();
    vector color;
    assign(&color, 0.0, 0.0, 0.0);
  file = fopen(filename, "w");
  size = resolution * 100;
  fprintf(file, "P3 %d %d 255\n", size, size);
  inc = 1.0/(double)resolution;
  y = 50.0;
  for (j = 0; j < size; j++) {
    x = -50.0;
    for (i = 0; i < size; i++) {
      colorAt(x, y, theworld, &color);
      multiply(&color, 255.0);
      vectorIntegerPrintf(file, &color);
      x += inc;
    }
    y -= inc;
  }
  fclose(file);
}

void colorAt(double x, double y,
	     world *theworld,
	     vector *color){
  //vector pos = vectorMalloc();
    vector pos;
  assign(&pos, x, y, 0.0);
  //ray myray = rayMalloc();
    ray myray;
  myray.position = theworld->eye;
  subtract(&myray.direction, &pos, &theworld->eye);
  sendRay(&myray, theworld, color);
}

void sendRay(ray *myray,    /* in */
	     world *theworld, /* in */
	     vector *color  /* out */) {
/* find color of what ray hits in the world */
  int success;
  //vector pos = vectorMalloc();
    vector pos;
    assign(&pos, 0.0, 0.0, 0.0);
  //sphere mysphere = sphereMalloc();
    sphere mysphere;
    assign(&mysphere.center, 0.0, 0.0, 0.0);
    mysphere.radius = 1.0;
    assign(&mysphere.color, 0.5, 0.5, 0.5);
  firstHit(myray, theworld, &success, &pos, &mysphere);
  if (success) {
    lambert(&mysphere, &pos, theworld, color);
  } else {
    copy(color, &theworld->backgroundColor);
  }
}

void lambert(sphere *mysphere, /* in */
	     vector *pos,     /* in */
	     world  *theworld,   /* in */
	     vector *color    /* out */) {
/* find color of pos on sphere in world, using lambert shading */
  //vector norm = vectorMalloc();
    vector norm;
    assign(&norm, 0.0, 0.0, 0.0);
  double value;
  sphereNormal(mysphere, pos, &norm);
  value = dot(&norm, &theworld->light);
  if (value < 0.0) {
    value = 0.0;
  }
  copy(color, &mysphere->color);
  multiply(color, value);
}

void firstHit(ray *myray,      /* in */
	      world *theworld,  /* in */
	      int* success,  /* out */
	      vector *pos,    /* out */
	      sphere *mysphere  /* out */) {
/* find first hit of ray in world
   success is false if no hit
   sphere and position of closest hit returned otherwise */
  double dist, tmpDist;
  //vector tmpPos = vectorMalloc();
    vector tmpPos;
    assign(&tmpPos, 0.0, 0.0, 0.0);
  int tmpSuccess, i;
  dist = 1.0e20;
  *success = 0;
  for (i = theworld->length-1; i >=0; i--) {
    intersect(theworld->objects[i], myray, &tmpSuccess, &tmpPos);
    if (tmpSuccess) {
      tmpDist = distance(&theworld->eye, &tmpPos);
      if (tmpDist < dist) {
	*success = 1;
	dist = tmpDist;
	copy(pos, &tmpPos);
	sphereCopy(mysphere, theworld->objects[i]);
      }
    }
  }
}

void intersect(sphere *mysphere, /* in */
	       ray *myray,      /* in */
	       int* success,  /* out */
	       vector *pos     /* out */) {
/* determine if ray intersects sphere
   success is false if no intersection
   pos is position of intersection otherwise */
  double a, b, c;
  //vector p = vectorMalloc();
    vector p;
    //assign(&p, 0.0, 0.0, 0.0);
  int nroots;
  double root1, root2;
  a = dot(&myray->direction, &myray->direction);
  subtract(&p, &myray->position, &mysphere->center);
  b = 2.0*dot(&p, &myray->direction);
  c = dot(&p, &p) - mysphere->radius*mysphere->radius;
  quadratic(a,b,c, &nroots, &root1, &root2);
  if (nroots == 0) {
    *success = 0;
  } else if (root1 > 0.0) {
    *success = 1;
    copy(pos, &myray->direction);
    multiply(pos, root1);
    add(pos, &myray->position, pos);
  } else if (root2 > 0.0) {
    *success = 1;
    copy(pos, &myray->direction);
    multiply(pos, root2);
    add(pos, &myray->position, pos);
  } else {
    *success = 0;
  }
}

