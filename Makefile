.PHONY=clean distclean timings scalasca 
CFLAGS:=-fopenmp -O3 -g -std=c99 -mtune=native -march=native
CC=gcc

omp: omp.c

clean:
	rm -f omp

distclean: clean
	rm -rf epik* perf.*

timings: clean omp
	time ./omp

scalasca: CC:=scalasca -instrument ${CC}
scalasca: omp
	scalasca -analyse ./omp
