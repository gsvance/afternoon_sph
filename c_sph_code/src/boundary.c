// Boundary condition checker routine for the SPH

#include "boundary.h"

vector reflect_vector(vector v, int component, float value)
// Reflect v in the given component about the given value
{
	float c;
	int i;
	vector rv;

	if (component < 0 || component > 2)
	{
		printf("Error: unable to reflect about dimension %d.\n", component);
		exit(2);
	}

	c = v.xyz[component] - value;

	for (i = 0; i < 3; i++)
	{
		if (i == component)
			rv.xyz[i] = value - c;
		else
			rv.xyz[i] = v.xyz[i];
	}

	return rv;
}

void enforce_boundaries(particle * part)
// Reflect particles back into sim volume if they escape
{
	int xflag = 0, yflag = 0, zflag = 0, flag = 0;

	// X limits
	if (part->pos.xyz[0] < 0.0)
	{
		part->pos = reflect_vector(part->pos, 0, 0.0);
		flag = xflag = 1;
	}
	else if (part->pos.xyz[0] > XMAX)
	{
		part->pos = reflect_vector(part->pos, 0, XMAX);
		flag = xflag = 1;
	}

	// X velocity
	if (xflag)
		part->vel = reflect_vector(part->vel, 0, 0.0);

	// Y limits
	if (part->pos.xyz[1] < 0.0)
	{
		part->pos = reflect_vector(part->pos, 1, 0.0);
		flag = yflag = 1;
	}
	else if (part->pos.xyz[1] > YMAX)
	{
		part->pos = reflect_vector(part->pos, 1, YMAX);
		flag = yflag = 1;
	}

	// Y velocity
	if (yflag)
		part->vel = reflect_vector(part->vel, 1, 0.0);

	// Z limits
	if (part->pos.xyz[2] < 0.0)
	{
		part->pos = reflect_vector(part->pos, 2, 0.0);
		flag = zflag = 1;
	}
	else if (part->pos.xyz[2] > ZMAX)
	{
		part->pos = reflect_vector(part->pos, 2, ZMAX);
		flag = zflag = 1;
	}

	// Z velocity
	if (zflag)
		part->vel = reflect_vector(part->vel, 2, 0.0);

	// Lose energy from any boundary interactions
	if (flag)
		part->vel = vector_scale(VLOSS, part->vel);
}

