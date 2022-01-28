// File of SPH simulation parameters

#ifndef PARAMS_H
#define PARAMS_H

// Smoothing length
#define HLEN 2.0 // cm

// Number of particles
#define NPART 8000

// Mass of one particle
#define MPART 1.0 // g

// Strength of gravity
#define GRAV 981.0 // cm/s^2

// Strength of pressure, p = k*(rho-rho0)
//#define KPRES 2.197e10 // cm^2/s^2, speed of sound in water squared
//#define KPRES 1.3846e9 // cm^2/s^2, k_B * 300 K / (water molecule mass)
#define KPRES 800.0 // cm^2/s^2, tuned value that doesn't explode the simulation

// Equilibrium density of fluid
#define RHO0 1.0 // g/cm^3, normal density of water

// Strength of viscosity
//#define VMU 10.02 // dyn*s/cm^2, dynamic viscosity of water
#define VMU 10.0 // dyn*s/cm^2, tuned code value

// Velocity loss upon boundary interaction
#define VLOSS 0.70

// Spatial limits for the simulation
#define XMAX 200.0 // cm
#define YMAX 100.0 // cm
#define ZMAX 100.0 // cm

// Temporal limits for the simualtion
#define TSTEPS 400
#define TSTEP 0.005 // s

// Model write interval
#define MODINT 5

#endif

