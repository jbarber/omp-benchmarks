.PHONY=clean
CFLAGS:=-fopenmp -O3 -g -std=c99
CC:=gcc

omp: omp.c

timings: clean omp
	time ./omp

clean:
	rm omp
