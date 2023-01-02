all: main

in_out.o: in_out.h in_out.c
	gcc -c in_out.c -Wall

sudoku.o: sudoku.h sudoku.c 
	gcc -c sudoku.c -Wall `pkg-config --cflags MLV` 

main.o: main.c
	gcc -c main.c -Wall

main: in_out.o sudoku.o main.o 
	gcc -o main in_out.o sudoku.o main.o -lMLV -lm -Werror `pkg-config --cflags MLV` 

clean: 
	rm -f *.o
	rm -f *~
	rm -f main
