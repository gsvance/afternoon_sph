#!/usr/bin/env python

# Isometric visualization scheme for the SPH code

# Last modified 6/30/18 by Greg Vance

from vector import columnate

import sys
import numpy as np
import matplotlib.pyplot as plt

if len(sys.argv) != 2:
	raise SystemExit("error: provide name of *one* input file")

types = {"names": ("pid", "x", "y", "z", "vx", "vy", "vz"),
	"formats": tuple([np.int] + 6 * [np.float])}
data = np.loadtxt(sys.argv[1], dtype=types)

#pid = data["pid"]
#npart = pid.size

#pos = np.empty((npart, 3))
#pos[:,0], pos[:,1], pos[:,2] = data["x"], data["y"], data["z"]
x, y, z = data["x"], data["y"], data["z"]

#vel = np.empty((npart, 3))
#vel[:,0], vel[:,1], vel[:,2] = data["vx"], data["vy"], data["vz"]

xhat = np.array([np.cos(7.0 * np.pi / 6.0), np.sin(7.0 * np.pi / 6.0)])
yhat = np.array([np.cos(-np.pi / 6.0), np.sin(-np.pi / 6.0)])
zhat = np.array([0.0, 1.0])

proj = columnate(x) * xhat + columnate(y) * yhat + columnate(z) * zhat

xproj, yproj = proj[:,0], proj[:,1]
zproj = x + y + z

plt.plot(xproj, yproj, 'bo', markeredgecolor='darkblue')

bx = np.array([0.0, 150.0, 150.0, 150.0, 0.0, 0.0, 0.0])
by = np.array([0.0, 0.0, 0.0, 100.0, 100.0, 100.0, 0.0])
bz = np.array([100.0, 100.0, 0.0, 0.0, 0.0, 100.0, 100.0])

bound = columnate(bx) * xhat + columnate(by) * yhat + columnate(bz) * zhat
boundx, boundy = bound[:,0], bound[:,1]

plt.plot(boundx, boundy, 'k-')

plt.savefig('plot.png')
