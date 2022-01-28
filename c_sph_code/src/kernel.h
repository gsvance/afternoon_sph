// Header for the kernel functions

#ifndef KERNEL_H
#define KERNEL_H

#include "vector.h"

float kern_W(vector r_ij);
vector grad_W(vector r_ij);
float lapl_W(vector r_ij);

#endif

