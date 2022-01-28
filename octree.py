# Classes for the octree implementation used in the SPH code

# Last modified 6/30/18 by Greg Vance

class Point:
	def __init__(self, x, y, z, data=None):
		self.x, self.y, self.z = x, y, z
		self.data = data  # satellite data

class Box:
	def __init__(self, minCorner, maxCorner):
		self.minCorner, self.maxCorner = minCorner, maxCorner
	def containsPoint(self, pt):
		return (self.minCorner.x <= pt.x <= self.maxCorner.x \
			and self.minCorner.y <= pt.y <= self.maxCorner.y \
			and self.minCorner.z <= pt.z <= self.maxCorner.z)
	def intersectsBox(self, box):
		return not (self.minCorner.x > box.maxCorner.x \
			or self.maxCorner.x < box.minCorner.x \
			or self.minCorner.y > box.maxCorner.y \
			or self.maxCorner.y < box.minCorner.y \
			or self.minCorner.z > box.maxCorner.z \
			or self.maxCorner.z < box.minCorner.z)

OCTREE_NODE_CAPACITY = 8

class Octree:
	def __init__(self, region):
		self.region = region
		self.points = list()
		self.octants = None
	def insertPoint(self, pt):
		if not self.region.containsPoint(pt):
			return False
		if len(self.points) < OCTREE_NODE_CAPACITY:
			self.points.append(pt)
			return True
		if self.octants == None:
			self._subdivide()
		for octant in self.octants:
			if octant.insertPoint(pt):
				return True
		return False
	def _subdivide(self):
		minX = self.region.minCorner.x
		minY = self.region.minCorner.y
		minZ = self.region.minCorner.z
		maxX = self.region.maxCorner.x
		maxY = self.region.maxCorner.y
		maxZ = self.region.maxCorner.z
		midX = 0.5 * (minX + maxX)
		midY = 0.5 * (minY + maxY)
		midZ = 0.5 * (minZ + maxZ)
		self.octants = list()
		# lower x, lower y, lower z
		region = Box(Point(minX, minY, minZ), Point(midX, midY, midZ))
		self.octants.append(Octree(region))
		# upper x, lower y, lower z
		region = Box(Point(midX, minY, minZ), Point(maxX, midY, midZ))
		self.octants.append(Octree(region))
		# lower x, upper y, lower z
		region = Box(Point(minX, midY, minZ), Point(midX, maxY, midZ))
		self.octants.append(Octree(region))
		# lower x, lower y, upper z
		region = Box(Point(minX, minY, midZ), Point(midX, midY, maxZ))
		self.octants.append(Octree(region))
		# upper x, upper y, lower z
		region = Box(Point(midX, midY, minZ), Point(maxX, maxY, midZ))
		self.octants.append(Octree(region))
		# upper x, lower y, upper z
		region = Box(Point(midX, minY, midZ), Point(maxX, midY, maxZ))
		self.octants.append(Octree(region))
		# lower x, upper y, upper z
		region = Box(Point(minX, midY, midZ), Point(midX, maxY, maxZ))
		self.octants.append(Octree(region))
		# upper x, upper y, upper z
		region = Box(Point(midX, midY, midZ), Point(maxX, maxY, maxZ))
		self.octants.append(Octree(region))
	def queryVolume(self, volume):
		pointsInVolume = list()
		if not self.region.intersectsBox(volume):
			return pointsInVolume
		for point in self.points:
			if volume.containsPoint(point):
				pointsInVolume.append(point)
		if self.octants == None:
			return pointsInVolume
		for octant in self.octants:
			pointsInVolume.extend(octant.queryVolume(volume))
		return pointsInVolume;

