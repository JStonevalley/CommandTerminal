SRC=$(wildcard *.c)

peel: $(SRC)
	gcc -pedantic -Wall -ansi -O4 -o $@ $^