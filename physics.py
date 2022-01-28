# Physics solvers for SPH

# Solvers for the Navier-Stokes equations from
# https://www.youtube.com/watch?v=SQPCXzqH610
# Relevant equations are on slide 12 at about 18:39
# Also there in another form on slide 14 at about 25:36

# Last modified 6/30/18 by Greg Vance

from octree import Point, Box, Octree
from params import XMIN, YMIN, ZMIN, XMAX, YMAX, ZMAX, OVERLAP
from params import MPART, KPRES, RHO0, VMU, GRAV
from kernel import kern_W, grad_W, lapl_W
from vector import columnate, vectorsum

import numpy as np

# Wrapper class to handle the densities and physics equations internally
class PhysicsSolver:
	
	def __init__(self, pos, vel):
		self.npart = pos.size / 3
		assert pos.shape == (self.npart, 3)
		assert vel.shape == (self.npart, 3)
		self.pos, self.vel = pos, vel
		self._buildOctree()
		self.rho, self.pgrad, self.visc, self.acc = None, None, None, None
	
	def _buildOctree(self):
		minCorner = Point(XMIN, YMIN, ZMIN)
		maxCorner = Point(XMAX, YMAX, ZMAX)
		self.octree = Octree(Box(minCorner, maxCorner))
		for i in xrange(self.npart):
			xi, yi, zi = self.pos[i]
			self.octree.insertPoint(Point(xi, yi, zi, i))
	
	def _getNeighbors(self, index, includeSelf=True):
		xi, yi, zi = self.pos[index]
		minCorner = Point(xi - OVERLAP, yi - OVERLAP, zi - OVERLAP)
		maxCorner = Point(xi + OVERLAP, yi + OVERLAP, zi + OVERLAP)
		volume = Box(minCorner, maxCorner)
		neighbor_points = self.octree.queryVolume(volume)
		neighbors = [pt.data for pt in neighbor_points]
		if not includeSelf:
			neighbors = [nb for nb in neighbors if nb != index]
		return neighbors
	
	def solveRho(self):
		if self.rho is not None:
			return
		self.rho = np.empty(self.npart)
		for i in xrange(self.npart):
			neighbors = self._getNeighbors(i)
			sep = self.pos[neighbors] - self.pos[i]
			self.rho[i] = np.sum(MPART * kern_W(sep))
	
	def solvePgrad(self):
		if self.pgrad is not None:
			return
		self.solveRho()
		self.pgrad = np.empty((self.npart, 3))
		pressure = KPRES * (self.rho - RHO0)
		p_rho_2 = pressure / self.rho**2
		for i in xrange(self.npart):
			neighbors = self._getNeighbors(i, includeSelf=False)
			sep = self.pos[neighbors] - self.pos[i]
			fac = MPART * (p_rho_2[i] + p_rho_2[neighbors])
			self.pgrad[i] = vectorsum(columnate(fac) * grad_W(sep))
	
	def solveVisc(self):
		if self.visc is not None:
			return
		self.solveRho()
		self.visc = np.empty((self.npart, 3))
		for i in xrange(self.npart):
			neighbors = self._getNeighbors(i, includeSelf=False)
			sep = self.pos[neighbors] - self.pos[i]
			dv = self.vel[neighbors] - self.vel[i]
			fac = MPART * (dv / columnate(self.rho[neighbors]))
			self.visc[i] = vectorsum(fac * columnate(lapl_W(sep)))
		self.visc *= columnate(VMU / self.rho)
	
	def solveAcc(self):
		if self.acc is not None:
			return
		self.solvePgrad()
		self.solveVisc()
		gravity = np.array([0.0, 0.0, -GRAV])
		self.acc = gravity - self.pgrad + self.visc
	
	def getRho(self):
		self.solveRho()
		return self.rho
	
	def getAcc(self):
		self.solveAcc()
		return self.acc

