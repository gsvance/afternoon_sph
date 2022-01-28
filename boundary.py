# Boundary constraints used in the SPH code

# Last modified 6/30/18 by Greg Vance

from params import XMIN, YMIN, ZMIN, XMAX, YMAX, ZMAX, VLOSS

import numpy as np

def reflectVector(vector, coord, about):
	assert vector.shape == (3,)
	index = {"x": 0, "y": 1, "z": 2}[coord]
	reflected = np.copy(vector)
	reflected[index] = about - (reflected[index] - about)
	return reflected

def constrain(pos, vel):
	npart = pos.size / 3
	assert pos.shape == (npart, 3)
	assert vel.shape == (npart, 3)
	for i in xrange(npart):
		if pos[i,0] < XMIN:
			pos[i] = reflectVector(pos[i], "x", XMIN)
			vel[i] = VLOSS * reflectVector(vel[i], "x", 0.0)
		elif pos[i,0] > XMAX:
			pos[i] = reflectVector(pos[i], "x", XMAX)
			vel[i] = VLOSS * reflectVector(vel[i], "x", 0.0)
		if pos[i,1] < YMIN:
			pos[i] = reflectVector(pos[i], "y", YMIN)
			vel[i] = VLOSS * reflectVector(vel[i], "y", 0.0)
		elif pos[i,1] > YMAX:
			pos[i] = reflectVector(pos[i], "y", YMAX)
			vel[i] = VLOSS * reflectVector(vel[i], "y", 0.0)
		if pos[i,2] < ZMIN:
			pos[i] = reflectVector(pos[i], "z", ZMIN)
			vel[i] = VLOSS * reflectVector(vel[i], "z", 0.0)
		elif pos[i,2] > ZMAX:
			pos[i] = reflectVector(pos[i], "z", ZMAX)
			vel[i] = VLOSS * reflectVector(vel[i], "z", 0.0)
	return pos, vel

