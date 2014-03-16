sudoku : sudoku.o
	gcc -o sudoku sudoku.o dicas.o completa.o -lpthread
	
sudoku.o : sudoku.c dicas.o completa.o
	gcc -fno-stack-protector -g -c sudoku.c
	
completa.o : completa.c completa.h
	gcc -fno-stack-protector -pthread -g -c completa.c
	
dicas.o : dicas.c dicas.h
	gcc -fno-stack-protector -pthread -g -c dicas.c
	
clean :
	rm sudoku sudoku.o dicas.o completa.o
