FILES = wordstat.c node.c
CFLAGS = -ansi -pedantic -Wall

all:
	gcc $(FILES) $(CFLAGS) -o wordstat
clean:
	rm wordstat
debug:
	gcc $(FILES) $(CFLAGS) -g -o wordstat