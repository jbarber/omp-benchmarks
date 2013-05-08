.PHONY=clean
CFLAGS:=-fopenmp -O3 -g -std=c99

omp: omp.c

clean:
	rm omp
