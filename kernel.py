# Kernel function implementation used in the SPH code

# Last modified 6/30/18 by Greg Vance

# SPH kernel function and derivatives taken from
# https://www.youtube.com/watch?v=SQPCXzqH610
# The particular equations are on slide 13 at 22:47 in the video lecture

from params import HLEN
from vector import columnate, dotprod, magnitude

import numpy as np

# The kernel, probably your usual cubic spline function
def kern_W(sep):
	const = 315.0 / (64.0 * np.pi * HLEN**9)
	dist_sqr = dotprod(sep, sep)
	quad = HLEN**2 - dist_sqr
	return const * (quad > 0.0) * quad**3

# Gradient of the kernel function, result is a vector
def grad_W(sep):
	const = -45.0 / (np.pi * HLEN**6)
	dist = magnitude(sep)
	lin = HLEN - dist
	fac = const * lin**2 / dist
	return columnate(fac * (lin > 0.0)) * sep

# Laplacian of the kernel function
def lapl_W(sep):
	const = 45.0 / (np.pi * HLEN**6)
	dist = magnitude(sep)
	lin = HLEN - dist
	return const * (lin > 0.0) * lin

