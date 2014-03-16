#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "dicas.h"
#include "completa.h"

#define TAB_LARG 9
#define TAB_ALT 9

int main(){
	
	
	
	char tabuleiro[TAB_LARG][TAB_ALT] = {{'X', '6', '1', 'X', 'X', 'X', 'X', '9', 'X'}
										,{'4', '3', 'X', 'X', '9', '5', 'X', '6', 'X'}
										,{'9', 'X', 'X', '1', 'X', '2', 'X', 'X', '3'}
										,{'X', 'X', 'X', '4', 'X', '1', 'X', 'X', '9'}
										,{'5', 'X', '9', 'X', 'X', 'X', '7', 'X', '1'}
										,{'6', 'X', 'X', '2', 'X', '9', 'X', 'X', 'X'}
										,{'3', 'X', 'X', '9', 'X', '8', 'X', 'X', '6'}
										,{'X', '8', 'X', '7', '3', 'X', 'X', '4', '2'}
										,{'X', '9', 'X', 'X', 'X', 'X', '3', '1', 'X'}
										};
	/*
	char tabuleiro[TAB_LARG][TAB_ALT] = {{'8', '6', '1', '3', '4', '7', '2', '9', '1'}
										,{'4', 'X', '2', '8', '9', '5', '1', '6', '7'}
										,{'9', '5', '7', '1', '6', '2', '4', '8', '3'}
										,{'X', 'X', 'X', '4', 'X', '1', 'X', 'X', '9'}
										,{'5', 'X', '9', 'X', 'X', 'X', '7', 'X', '1'}
										,{'6', 'X', 'X', '2', 'X', '9', 'X', 'X', 'X'}
										,{'3', 'X', 'X', '9', 'X', '8', 'X', 'X', '6'}
										,{'X', '8', 'X', '7', '3', 'X', 'X', '4', '2'}
										,{'X', '9', 'X', 'X', 'X', 'X', '3', '1', 'X'}
										};
	*/
	int value = dicas(tabuleiro);
	int completou = completa(tabuleiro, 0, 0);
	
	int i, j;
	for(i = 0; i < TAB_ALT; i++){
		if(i%3 == 0 && i != 0){
			printf("\n");
		}
		for(j = 0; j < TAB_LARG; j++){
			if(j%3 == 0 && j != 0){
				printf(" ");
			}
			printf("[%c]", tabuleiro[i][j]);
		}
		printf("\n");
	}
	
	return 0;	
}
