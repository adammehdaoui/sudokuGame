CC := gcc
CFLAGS := -Wall -std=c17
LDLIBS := -lMLV -lm -Werror
OBJ := in_out.o display.o sudoku.o main.o
MAIN := sudoku

all: sudoku

in_out.o: include/in_out.h src/in_out.c
	$(CC) -c src/in_out.c $(CFLAGS)

display.o: include/display.h src/display.c
	$(CC) -c src/display.c $(CFLAGS)

sudoku.o: include/sudoku.h src/sudoku.c 
	$(CC) -c src/sudoku.c $(CFLAGS)

main.o: src/main.c
	$(CC) -c src/main.c $(CFLAGS)

sudoku: $(OBJ)
	$(CC) -o $(MAIN) $(OBJ) $(LDLIBS)

run: $(OBJ)
	$(CC) -o $(MAIN) $(OBJ) $(LDLIBS)
	./$(MAIN) grid1.txt

clean: 
	rm -f *.o
	rm -f *~
	rm -f sudoku
