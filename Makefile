CC = g++
CFLAGS = -g -Wall -O3
EXEC = main

all: $(EXEC)

$(EXEC): $(EXEC).cpp
	$(CC) $(CFLAGS) $< -o $@

run:
	make && ./main > image.ppm && eog image.ppm


.PHONY:
	clean

clean:
	rm -rf $(EXEC) image.ppm
