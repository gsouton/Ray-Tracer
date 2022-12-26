CC = g++
CFLAGS = -Wall
EXEC = main

all: $(EXEC)

$(EXEC): $(EXEC).cpp
	$(CC) $(CFLAGS) $< -o $@

run:
	make && ./main > image.ppm


.PHONY:
	clean

clean:
	rm -rf $(EXEC) image.ppm
