sudoku : sudoku.o
	gcc -o sudoku sudoku.o dicas.o completa.o verificacao.o -lpthread
	
sudoku.o : sudoku.c dicas.o completa.o verificacao.o
	gcc -fno-stack-protector -g -c sudoku.c
	
verificacao.o : verificacao.c verificacao.h dicas.o
	gcc -fno-stack-protector -pthread -g -c verificacao.c
	
completa.o : completa.c completa.h dicas.o
	gcc -fno-stack-protector -pthread -g -c completa.c
	
dicas.o : dicas.c dicas.h
	gcc -fno-stack-protector -pthread -g -c dicas.c
	
clean :
	rm sudoku sudoku.o dicas.o completa.o verificacao.o
