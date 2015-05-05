SRC=$(wildcard *.c)

shell: $(SRC)
	gcc -pedantic -Wall -ansi -O4 -o $@ $^