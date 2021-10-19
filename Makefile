CC=gcc
OPTS=-Wall -O3 -march=native 

all: simulation
	./simulation
	gnuplot plot-simulation.gp

simulation: simulation.c
	$(CC) $(OPTS) simulation.c -o simulation -lm


clean:
	rm -f *.o simulation
	rm -f *dat

.PHONY: clean all