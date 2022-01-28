# File of SPH simulation parameters

# Last modified 6/30/18 by Greg Vance

# Smoothing length
HLEN = 2.0 # cm

# Range for particle kernel overlap
OVERLAP = 2.0 * HLEN

# Mass of one particle
MPART = 1.0 # g

# Strength of gravity
GRAV = 981.0 # cm/s^2

# Strength of pressure, p = k*(rho-rho0)
#KPRES = 2.197e10 # cm^2/s^2, speed of sound in water squared
#KPRES 1.3846e9 # cm^2/s^2, k_B * 300 K / (water molecule mass)
KPRES = 800.0 # cm^2/s^2, tuned value that doesn't explode the simulation

# Equilibrium density of fluid
RHO0 = 1.0 # g/cm^3, normal density of water

# Strength of viscosity
#VMU = 10.02 # dyn*s/cm^2, dynamic viscosity of water
VMU = 10.0 # dyn*s/cm^2, tuned code value

# Velocity loss upon boundary interaction
VLOSS = 0.70

# Spatial limits for the simulation
XMIN = 0.0 # cm
YMIN = 0.0 # cm
ZMIN = 0.0 # cm
XMAX = 150.0 # cm
YMAX = 100.0 # cm
ZMAX = 100.0 # cm

# Temporal limits for the simualtion
TSTEPS = 200
TSTEP = 0.005 # s

# Model write interval
MODINT = 5

