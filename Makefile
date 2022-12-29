CC = g++
CFLAGS = -std=c++17 -g -Wall -O3 -fopenmp -lpthread
INC=-Ivendors/stb
EXEC = main

all: $(EXEC)

$(EXEC): $(EXEC).cpp
	$(CC) $(CFLAGS) $(INC) $< -o $@

run:
	make clean && make && ./main  && eog image.png

ppm:
	make clean && make && ./main > image.ppm && eog image.ppm

PHONY:
	clean

clean:
	rm -rf $(EXEC) *.ppm *.png *.bmp
