#!/bin/bash

# Run code with decreasing numbers of threads
set -ue

: ${MAXTHREADS:=16}
echo "threads user system elapsed cpu";
for i in $(eval echo {${MAXTHREADS}..1}); do
    echo -n "$i ";
    OMP_NUM_THREADS=$i time ./omp 2>&1
done | sed '/inputs/d; s/[[:alpha:]]//g; s/%.*//'
