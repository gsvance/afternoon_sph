#!/bin/bash
# Translate everything to ascii

for x in {00000..00400..5}; do
	./asciiread cube/test${x}.model cubeascii/test${x}.txt
done

