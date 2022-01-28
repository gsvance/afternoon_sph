// Header for vector struct and usage functions

#ifndef VECTOR_H
#define VECTOR_H

#include <math.h>
#include <stdio.h>

struct VECTOR_STRUCT {
	float xyz[3];
};

typedef struct VECTOR_STRUCT vector;

vector vector_make(float x, float y, float z);
vector vector_zero();
vector vector_add(vector v1, vector v2);
vector vector_scale(float a, vector v);
vector vector_subtract(vector v1, vector v2);
float vector_dot(vector v1, vector v2);
float vector_magnitude(vector v);
void vector_print(vector v);

#endif

