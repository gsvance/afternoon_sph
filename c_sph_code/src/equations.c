// Solvers for the Navier-Stokes equations from https://www.youtube.com/watch?v=SQPCXzqH610
// Relevant equations are on slide 12 at about 18:39
// Also there in another form on slide 14 at about 25:36

#include "equations.h"

float density_solve(particle * part, particle ** neighbors, int n_neighbors)
// Solve the equation for the density using nearby particles
// Equation 2 from the video
{
	int j;
	float rho_i = 0.0;
	vector r_rb;

	for (j = 0; j < n_neighbors; j++)
	{
		r_rb = vector_subtract(neighbors[j]->pos, part->pos);
		rho_i += neighbors[j]->mass * kern_W(r_rb);
	}

	return rho_i;
}

float pressure(float rho)
// Return the pressure using the simple density-proportional form
// This is the equation from slide 7 at about 9:30
{
	return KPRES * (rho - RHO0);
}

vector pgrad_solve(particle * part, particle ** neighbors, int n_neighbors)
// Solve the equation for the pressure gradient using nearby particles
// Equation 3 from the video
{
	int j;
	vector gradp_rho = vector_zero();
	vector r_rb;
	float pi_rhoi_2, pj_rhoj_2, scal;
	vector term;

	pi_rhoi_2 = pressure(part->rho) / (part->rho * part->rho);

	for (j = 0; j < n_neighbors; j++)
	{
		// Avoid adding the particle itself at zero distance
		if (neighbors[j]->id == part->id)
			continue;

		r_rb = vector_subtract(neighbors[j]->pos, part->pos);

		pj_rhoj_2 = pressure(neighbors[j]->rho) / (neighbors[j]->rho * neighbors[j]->rho);
		scal = neighbors[j]->mass * (pi_rhoi_2 + pj_rhoj_2);

		term = vector_scale(scal, grad_W(r_rb));
		gradp_rho = vector_add(gradp_rho, term);
	}

	return gradp_rho;
}

vector visc_solve(particle * part, particle ** neighbors, int n_neighbors)
// Solve the equation for the viscous term using nearby particles
// Equation 4 from the video
{
	int j;
	vector visc = vector_zero();
	vector r_rb;
	vector dv_ji;
	float scal;
	vector term;

	for (j = 0; j < n_neighbors; j++)
	{
		// Skip the particle itself with dv_ji = 0
		if (neighbors[j]->id == part->id)
			continue;

		r_rb = vector_subtract(neighbors[j]->pos, part->pos);
		dv_ji = vector_subtract(neighbors[j]->vel, part->vel);

		scal = (neighbors[j]->mass / neighbors[j]->rho) * lapl_W(r_rb);
		term = vector_scale(scal, dv_ji);

		visc = vector_add(visc, term);
	}

	return vector_scale(VMU / part->rho, visc);
}

vector gravity()
// Return the acceleration vector representing gravity
{
	return vector_make(0.0, 0.0, -GRAV);
}

vector accel_solve(particle * part)
// Take a particle and work out its acceleration as a final step
// Equation 1 from the video
{
	vector acc;

	acc = gravity();
	acc = vector_subtract(acc, part->pgrad);
	acc = vector_add(acc, part->visc);

	return acc;
}

