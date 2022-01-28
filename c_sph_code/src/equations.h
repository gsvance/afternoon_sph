// Header file for the Navier-Stokes equations solvers

#ifndef EQUATIONS_H
#define EQUATIONS_H

#include "kernel.h"
#include "vector.h"
#include "particle.h"

float density_solve(particle * part, particle ** neighbors, int n_neighbors);
vector pgrad_solve(particle * part, particle ** neighbors, int n_neighbors);
vector visc_solve(particle * part, particle ** neighbors, int n_neighbors);
vector accel_solve(particle * part);

#endif

