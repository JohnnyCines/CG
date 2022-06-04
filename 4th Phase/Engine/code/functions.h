#include <stdlib.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <math.h>

void buildRotMatrix(float* x, float* y, float* z, float* m);
void cross(float* a, float* b, float* res);
void normalize(float* a);
float length(float* v);
void multMatrixVector(float* m, float* v, float* res); 
void getCatmullRomPoint(float t, float* p0, float* p1, float* p2, float* p3, float* pos, float* deriv);
void getGlobalCatmullRomPoint(float gt, float* pos, float* deriv, float** p, int pcount);
void renderCatmullRomCurve(float** p, int pcount);