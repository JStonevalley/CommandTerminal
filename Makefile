SRC=$(wildcard *.c)

main.o: $(SRC)
	gcc -pedantic -Wall -ansi -O4 -o $@ $^