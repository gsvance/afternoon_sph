# Vector operations used in the SPH code

# Last modified 6/30/18 by Greg Vance

import numpy as np

def columnate(row):
	return np.reshape(row, (row.size, 1))

def magnitude(vectors):
	return np.linalg.norm(vectors, axis=1)

def dotprod(a_vectors, b_vectors):
	return np.sum(a_vectors * b_vectors, axis=1)

def vectorsum(vectors):
	return np.sum(vectors, axis=0)

