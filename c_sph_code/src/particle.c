// Functions for particles and their interactions

#include "particle.h"

particle particle_make(float mass, vector pos, vector vel)

{
	static id = 0;
	particle created;

	created.mass = mass;
	created.pos = pos;
	created.vel = vel;

	created.id = id;
	id++;

	return created;
}

void particle_update(particle * part)
// Update the particle's velocity and position with Euler integration
// Note: the acceleration should be updated via equations.c before this
{
	vector dvel, dpos;

	dvel = vector_scale(TSTEP, part->acc);
	part->vel = vector_add(part->vel, dvel);

	dpos = vector_scale(TSTEP, part->vel);
	part->pos = vector_add(part->pos, dpos);
}

