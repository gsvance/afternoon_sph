// Code for routines that step time forwards

#include "stepper.h"

void advance_time(particle particles[], int tstep)
// Take the set of particles and step time forwards from tstep-1 to tstep
{
	float time = tstep * TSTEP; // s
	int voxels[NPART];
	particle ** neighbors;
	int n_neighbors;
	int n;
	char fname[100];

	printf("Running timestep %d with t=%.4f seconds...\n", tstep, time);

	// Sort particles by voxels
	sort_voxels(particles, voxels);

	// Solve the Navier-Stokes density equation for each particle
	// Densities need to be worked out BEFORE pressure grad and viscosity
	for (n = 0; n < NPART; n++)
	{
		neighbors = find_neighbors(particles, voxels, n, &n_neighbors);

		particles[n].rho = density_solve(&particles[n], neighbors, n_neighbors);

		free(neighbors);
	}
	
	// Solve the other Navier-Stokes equations for each particle
	for (n = 0; n < NPART; n++)
	{
		neighbors = find_neighbors(particles, voxels, n, &n_neighbors);

		particles[n].pgrad = pgrad_solve(&particles[n], neighbors, n_neighbors);
		particles[n].visc = visc_solve(&particles[n], neighbors, n_neighbors);
		particles[n].acc = accel_solve(&particles[n]);

		free(neighbors);
	}

	// Update all the particle velocities and positions
	// Enfoce the simulation boundaries while we're at it
	for (n = 0; n < NPART; n++)
	{
		particle_update(&particles[n]);
		enforce_boundaries(&particles[n]);
	}

	// Write files at appropriate times
	if (tstep % MODINT == 0)
	{
		sprintf(fname, "cube/test%05d.model", tstep);
		writefile(particles, fname);
	}
}

