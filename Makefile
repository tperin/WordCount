FILES = wordstat.c node.c
CFLAGS = -ansi -pedantic -Wall

all:
	gcc $(FILES) $(CFLAGS) wordstat
clean:
	rm wordstat