// Routines for voxel sorting methods

#include "voxels.h"

int voxel_1d(int xi, int yi, int zi)
// Take x, y, and z voxel indices and return a 1D index
{
	if (xi < 0 || xi >= XVOX)
		return -1;
	if (yi < 0 || yi >= YVOX)
		return -1;
	if (zi < 0 || zi >= ZVOX)
		return -1;

	return xi + XVOX * (yi + YVOX * zi);
}

void sort_voxels(particle particles[], int voxels[])
// For each particle, insert its 1D voxel index in the list
{
	int xi, yi, zi;
	int n;
	int vox;

	for (n = 0; n < NPART; n++)
	{
		xi = (int) (particles[n].pos.xyz[0] / VOXSIDE);
		yi = (int) (particles[n].pos.xyz[1] / VOXSIDE);
		zi = (int) (particles[n].pos.xyz[2] / VOXSIDE);

		// Super rare boundary condition
		if (xi == XVOX)
			xi--;
		if (yi == YVOX)
			yi--;
		if (zi == ZVOX)
			zi--;

		vox = voxel_1d(xi, yi, zi);

		if (vox == -1)
		{
			printf("Error: particle is outside simulation volume?\n");
			printf("%f %f %f\n", particles[n].pos.xyz[0], particles[n].pos.xyz[1], particles[n].pos.xyz[2]);
			printf("%f %f %f\n", particles[n].vel.xyz[0], particles[n].vel.xyz[1], particles[n].vel.xyz[2]);
			exit(3);
		}

		voxels[n] = vox;
	}
}

void voxel_3d(int vox, int * xi, int * yi, int * zi)
// Take 1D voxel index and return the 3D indices via pointers
{
	static const int zlayer = XVOX * YVOX;

	*zi = vox / zlayer;
	vox %= zlayer;
	
	*yi = vox / XVOX;
	*xi = vox % XVOX;
}

int in_pvoxels(int vox, int pvoxels[8])
// Return whether vox is in the 8-element array pvoxels
{
	int i;

	for (i = 0; i < 8; i++)
		if (pvoxels[i] == vox)
			return 1;

	return 0;
}

particle ** find_neighbors(particle particles[], int voxels[], int p, int * n_neighbors)
// Return pointer to array of pointers to neighbor particles to particle p
// Uses particle and voxel lists, returns number of neighbors via a pointer
{
	static const float half = 0.5 * VOXSIDE;
	particle ** neighbors;
	int pvoxels[8];
	int vox, xi, yi, zi;
	int xside, yside, zside;
	int n, i;

	vox = voxels[p];
	voxel_3d(vox, &xi, &yi, &zi);

	if (particles[p].pos.xyz[0] - xi*VOXSIDE < half)
		xside = -1;
	else
		xside = +1;

	if (particles[p].pos.xyz[1] - yi*VOXSIDE < half)
		yside = -1;
	else
		yside = +1;

	if (particles[p].pos.xyz[2] - zi*VOXSIDE < half)
		zside = -1;
	else
		zside = +1;

	pvoxels[0] = vox;
	pvoxels[1] = voxel_1d(xi + xside, yi, zi);
	pvoxels[2] = voxel_1d(xi, yi + yside, zi);
	pvoxels[3] = voxel_1d(xi, yi, zi + zside);
	pvoxels[4] = voxel_1d(xi + xside, yi + yside, zi);
	pvoxels[5] = voxel_1d(xi + xside, yi, zi + zside);
	pvoxels[6] = voxel_1d(xi, yi + yside, zi + zside);
	pvoxels[7] = voxel_1d(xi + xside, yi + yside, zi + zside);

	*n_neighbors = 0;
	for (n = 0; n < NPART; n++)
		if (in_pvoxels(voxels[n], pvoxels))
			(*n_neighbors)++;

	neighbors = malloc(*n_neighbors * sizeof(particle *));
	if (neighbors == NULL)
	{
		printf("Error: allocation for neighbors array failed.\n");
		exit(4);
	}

	i = 0;
	for (n = 0; n < NPART; n++)
		if (in_pvoxels(voxels[n], pvoxels))
			neighbors[i++] = &particles[n];

	return neighbors;
}

