#!/usr/bin/env python

# Make-a da plots

# Last modified 6/30/18 by Greg Vance

import subprocess as sp
import os

for x in xrange(0, 405, 5):
	infile = "cube_models/model%06d.sph" % (x)
	print infile
	sp.call(["python", "isovis.py", infile], shell=True)
	plotname = "visuals/plot%06d.png" % (x)
	os.rename("plot.png", plotname)
