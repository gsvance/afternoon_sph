#!/usr/bin/env python

# Main driver routine for the simulation that runs everything

# Last modified 6/30/18 by Greg Vance

from params import HLEN, MPART, TSTEPS, TSTEP, MODINT
from physics import PhysicsSolver
from boundary import constrain

import sys
import numpy as np

if len(sys.argv) != 2:
	raise SystemExit("error: provide name of *one* input file")

types = {"names": ("pid", "x", "y", "z", "vx", "vy", "vz"),
	"formats": tuple([np.int] + 6 * [np.float])}
data = np.loadtxt(sys.argv[1], dtype=types)

pid = data["pid"]
npart = pid.size

pos = np.empty((npart, 3))
pos[:,0], pos[:,1], pos[:,2] = data["x"], data["y"], data["z"]

vel = np.empty((npart, 3))
vel[:,0], vel[:,1], vel[:,2] = data["vx"], data["vy"], data["vz"]

#hsml = HLEN * np.ones(npart)
#mass = MPART * np.ones(npart)

for iteration in xrange(1, TSTEPS + 1):
	
	print "Running timestep %d..." % (iteration)
	
	solve = PhysicsSolver(pos, vel)
	acc = solve.getAcc()
	
	dt = TSTEP
	
	vel += acc * dt
	pos += vel * dt
	
	pos, vel = constrain(pos, vel)
	
	if iteration % MODINT == 0:
		filename = "model%06d.sph" % (iteration)
		print "Writing file %s..." % (filename)
		np.savetxt(filename, np.column_stack((pid, pos, vel)),
			header="pid x y z vx vy vz")

# cleanup

