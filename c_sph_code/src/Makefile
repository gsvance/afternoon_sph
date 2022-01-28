PROG = ../sph

all: $(PROG) ../asciiread

$(PROG): boundary.o equations.o kernel.o main.o particle.o setup.o stepper.o vector.o voxels.o writer.o
	gcc boundary.o equations.o kernel.o main.o particle.o setup.o stepper.o vector.o voxels.o writer.o -o $(PROG) -lm

../asciiread: asciiread.o reader.o writer.o
	gcc asciiread.o reader.o writer.o -o ../asciiread
asciiread.o: asciiread.c particle.h params.h reader.h writer.h
	gcc -c asciiread.c

boundary.o: boundary.c boundary.h particle.h params.h vector.h
	gcc -c boundary.c
equations.o: equations.c equations.h kernel.h vector.h particle.h
	gcc -c equations.c
kernel.o: kernel.c kernel.h vector.h
	gcc -c kernel.c
main.o: main.c main.h particle.h setup.h stepper.h writer.h
	gcc -c main.c
particle.o: particle.c particle.h vector.h params.h
	gcc -c particle.c
reader.o: reader.c reader.h particle.h params.h
	gcc -c reader.c
setup.o: setup.c setup.h particle.h vector.h params.h
	gcc -c setup.c
stepper.o: stepper.c stepper.h particle.h voxels.h boundary.h equations.h writer.h
	gcc -c stepper.c
vector.o: vector.c vector.h
	gcc -c vector.c
voxels.o: voxels.c voxels.h particle.h
	gcc -c voxels.c
writer.o: writer.c writer.h particle.h params.h
	gcc -c writer.c

clean:
	rm -rf $(PROG) ../asciiread *.o

