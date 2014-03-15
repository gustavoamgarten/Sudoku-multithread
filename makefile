sudoku : sudoku.o
	gcc -o sudoku sudoku.o dicas.o
	
sudoku.o : sudoku.c dicas.o
	gcc -fno-stack-protector -g -c sudoku.c
	
dicas.o : dicas.c
	gcc -fno-stack-protector -g -c dicas.c
	
clean :
	rm sudoku sudoku.o dicas.o
