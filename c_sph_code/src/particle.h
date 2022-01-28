// Header for defining particles and their interactions

#ifndef PARTICLE_H
#define PARTICLE_H

#include "vector.h"
#include "params.h"

struct PARTICLE_STRUCT {
	float mass;
	int id;
	float rho;
	vector pgrad;
	vector visc;
	vector pos, vel, acc;
};

typedef struct PARTICLE_STRUCT particle;

// Functions for making and updating particles
particle particle_make(float mass, vector pos, vector vel);
void particle_update(particle * part);

#endif

