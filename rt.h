#ifndef RT_H
#define RT_H
#include "la.h"

namespace rt {
  struct ray {
    la::vector pos;
    la::vector direction;
  ray():
    pos(la::vector()), direction(la::vector()) {};
  ray(la::vector pp, la::vector dd):
    pos(pp), direction(dd) {};
  };
  
  struct sphere {
    la::vector pos;
    double radius;
    la::vector color;
  sphere():
    pos(la::vector()), radius(1.0), color(la::vector(0.5,0.5,0.5)) {};
  sphere(la::vector pp, double rr, la::vector cc):
    pos(pp), radius(rr), color(cc) {};
  };
  
  const int arrayMax = 500;

  typedef sphere objectArray[arrayMax];

  struct world {
    la::vector eye;
    la::vector light;
    objectArray objects;
    int length;
    la::vector backgroundColor;
  world():
    length(0), backgroundColor(la::vector(0.5, 0.75, 1.00)) {};
  };
  
  void addSphere(world & w, sphere  s);
  
  void quadratic(double a, double b, double c,
		 int& n,
		 double& s1, double& s2);
  
  void sphereNormal(sphere  s,
		    la::vector pos,
		    la::vector& norm);
  
  void tracer(string filename,
	      int resolution,
	      world  world);
  
  void colorAt(double x, double y,
	       world  world,
	       la::vector& color);
  
  void sendRay(ray  ray,
	       world  world,
	       la::vector& color);
  void lambert(sphere  sphere,
	       la::vector pos,
	       world  world,
	       la::vector& color);
  
  void firstHit(ray  ray,
		world  world,
		bool& success,
		la::vector& pos,
		sphere & sphere);
  
  void intersect(sphere  sphere,
		 ray  ray,
		 bool& success,
		 la::vector& pos);
  
}
#endif
  
