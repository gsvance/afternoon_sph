// SPH kernel function and derivatives taken from https://www.youtube.com/watch?v=SQPCXzqH610
// The particular equations are on slide 13 at 22:47 in the video lecture

#include "kernel.h"
#include "params.h"

// Useful large powers of the smoothing length
#define HSQR (HLEN*HLEN)
#define HSIX (HSQR*HSQR*HSQR)
#define HNINE (HSIX*HSQR*HLEN)

float kern_W(vector r_ij)
// The kernel, probably your usual cubic spline function
{
	static const float cons = 315.0 / (64.0 * M_PI * HNINE);
	float dist_sqr, quad;

	dist_sqr = vector_dot(r_ij, r_ij);
	quad = HSQR - dist_sqr;

	return (quad > 0.0) ? (cons * quad*quad*quad) : 0.0;
}

vector grad_W(vector r_ij)
// Gradient of the kernel function, result is a vector
{
	static const float cons = -45.0 / (M_PI * HSIX);
	float dist, line, scal;

	dist = vector_magnitude(r_ij);
	line = HLEN - dist;

	if (line <= 0.0)
		return vector_zero();

	scal = cons * line*line / dist;
	return vector_scale(scal, r_ij);
}

float lapl_W(vector r_ij)
// Laplacian of the kernel function
{
	static const float cons = 45.0 / (M_PI * HSIX);
	float dist, line;

	dist = vector_magnitude(r_ij);
	line = HLEN - dist;

	return (line > 0.0) ? (cons * line) : 0.0;
}

