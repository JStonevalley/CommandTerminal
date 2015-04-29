SRC=$(wildcard *.c)

all: $(SRC)
	gcc -pedantic -Wall -ansi -O4 -o $@ $^