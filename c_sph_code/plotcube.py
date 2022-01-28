# Plot the outputs from the cube sph sim

import numpy as np
import matplotlib.pyplot as plt

for x in xrange(0, 401, 5):

	print "Plotting timestep", x

	fname = "cubeascii/test%05d.txt" % (x)
	mass, pid, rho, pgrad_x, pgrad_y, pgrad_z, visc_x, visc_y, visc_z, pos_x, pos_y, pos_z, vel_x, vel_y, vel_z, acc_x, acc_y, acc_z = np.loadtxt(fname, unpack=True)

	fig = plt.figure("Frame %d" % (x))
	plt.plot(pos_x, pos_z, "bo")
	
	plt.xlim(-10, 210)
	plt.ylim(-5, 105)
	
	plt.xlabel("x (cm)")
	plt.ylabel("z (cm)")
	
	plt.title("t = %.4f s" % (x * 0.005))
	plt.savefig("cubeplot/test%05d.png" % (x))

	plt.close(fig)
