#!/usr/bin/env python

# File with the routines that set up the simulation

# Last modified 6/30/18 by Greg Vance

import numpy as np

# Simple routine to make a 20cm x 20cm x 20cm cube of particles

NPART = 8000

cubeside = 20 # particles
cubedim = 20.0 # cm
spacing = cubedim / cubeside # cm

jostle = cubedim / 40.0 # cm

xcorner = 50.0 - 0.5 * cubedim # cm
ycorner = 50.0 - 0.5 * cubedim # cm
zcorner = 50.0 - 0.5 * cubedim # cm

print "Setup routine running..."

# Set the position of the top cube corner
cubecorner = np.array([xcorner, ycorner, zcorner])

# Check that things work out
if cubeside**3 != NPART:
	raise SystemExit("error: particle cube dimensions don't work")

i, j, k = 0, 0, 0

pos = np.empty((NPART, 3))
vel = np.empty((NPART, 3))

# Generate the cube
for n in xrange(NPART):
	
	pos[n] = cubecorner + spacing * np.array([i, j, k])
	pos[n] += jostle * (2.0 * np.random.rand(3) - 1.0)
	vel[n] = np.zeros(3)
	
	# Increment positions
	i += 1
	if i == cubeside:
		i = 0
		j += 1
		if j == cubeside:
			j = 0
			k += 1

print "Successfully created %d particles." % (NPART)

pid = np.arange(NPART, dtype=np.int)

np.savetxt("cube000000.sph", np.column_stack((pid, pos, vel)),
	tuple(["%d"] + 6 * ["%e"]), header="pid x y z vx vy vz")

