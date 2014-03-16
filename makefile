sudoku : sudoku.o
	gcc -o sudoku sudoku.o dicas.o -lpthread
	
sudoku.o : sudoku.c dicas.o
	gcc -fno-stack-protector -g -c sudoku.c
	
dicas.o : dicas.c dicas.h
	gcc -fno-stack-protector -pthread -g -c dicas.c
	
clean :
	rm sudoku sudoku.o dicas.o
