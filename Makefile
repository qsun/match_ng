all: matcher test

test: matcher.o test.c
	cc matcher.o test.c -o test -Wall -ggdb -O0

matcher.o: matcher.h matcher.c
	cc -c matcher.c -Wall

matcher: matcher.o main.c
	cc matcher.o main.c -o matcher -Wall

clean:
	rm *.o
	rm matcher	


.PHONY: all clean
