CC := gcc
CFLAGS := -Wall -std=c17
LDLIBS := -lMLV -lm -Werror

all: sudoku

in_out.o: include/in_out.h src/in_out.c
	$(CC) -c src/in_out.c $(CFLAGS)

sudoku.o: include/sudoku.h src/sudoku.c 
	$(CC) -c src/sudoku.c $(CFLAGS) `pkg-config --cflags MLV` 

main.o: src/main.c
	$(CC) -c src/main.c $(CFLAGS)

sudoku: in_out.o sudoku.o main.o 
	$(CC) -o sudoku in_out.o sudoku.o main.o $(LDLIBS) `pkg-config --cflags MLV` 

run: in_out.o sudoku.o main.o 
	$(CC) -o sudoku in_out.o sudoku.o main.o $(LDLIBS) `pkg-config --cflags MLV` 
	./sudoku grid1.txt

clean: 
	rm -f *.o
	rm -f *~
	rm -f sudoku
