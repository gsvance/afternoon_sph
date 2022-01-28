// Handling functions for a simple 3D vector struct

#include "vector.h"

vector vector_make(float x, float y, float z)
// Create a new vector with given xyz components
{
	vector created;

	created.xyz[0] = x;
	created.xyz[1] = y;
	created.xyz[2] = z;

	return created;
}

vector vector_zero()
// Return the zero vector
{
	return vector_make(0.0, 0.0, 0.0);
}

vector vector_add(vector v1, vector v2)
// Add two 3D vectors together
{
	int i;
	vector sum;

	for (i = 0; i < 3; i++)
		sum.xyz[i] = v1.xyz[i] + v2.xyz[i];

	return sum;
}

vector vector_scale(float a, vector v)
// Multiply a vector by a scalar
{
	int i;
	vector scaled;

	for (i = 0; i < 3; i++)
		scaled.xyz[i] = a * v.xyz[i];

	return scaled;
}

vector vector_subtract(vector v1, vector v2)
// Take the difference of two vectors v1 - v2
{
	vector minus_v2;

	minus_v2 = vector_scale(-1.0, v2);
	return vector_add(v1, minus_v2);
}

float vector_dot(vector v1, vector v2)
// Return the dot product of two vectors
{
	int i;
	float sum_quad = 0.0;

	for (i = 0; i < 3; i++)
		sum_quad += v1.xyz[i] * v2.xyz[i];

	return sum_quad;
}

float vector_magnitude(vector v)
// Return the vector magnitude of v
{
	return sqrtf(vector_dot(v, v));
}

void vector_print(vector v)
// Print out the components of v and a newline
{
	printf("(%f, %f, %f)\n", v.xyz[0], v.xyz[1], v.xyz[2]);
}

