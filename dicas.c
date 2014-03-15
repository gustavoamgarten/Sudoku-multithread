#include <stdio.h>
#include "dicas.h"

#define TAB_LARG 9
#define TAB_ALT 9

#define MAX_CASAS 81
#define MAX_NUM 9

//ASCII = Subtrair 48

int dicas(char tab[TAB_LARG][TAB_ALT]){
	
	int i, j, k, l, m, n;
	char dica[TAB_LARG][TAB_ALT];
	
	char possibilidades[MAX_CASAS][MAX_NUM + 1];
	int numDicas = 0;
	
	char seqLinha[MAX_NUM];
	char seqColuna[MAX_NUM];
	char seqQuadrado[MAX_NUM];
	int existeLinha = 0;
	int existeColuna = 0;
	int existeQuadrado = 0;
	int maxValue = 0;
	
	int inicioLinha, inicioColuna;
	
	for(i = 0; i < TAB_LARG; i++) {
		for(j = 0; j < TAB_ALT; j++){
			dica[i][j] = tab[i][j];
		}
	}
	
	for(i = 0; i < TAB_LARG; i++) {
		for(j = 0; j < TAB_ALT; j++){
			if(tab[i][j] == 'X') {
				
				maxValue = 0;
				
				// Percorre a linha (Pode ser jogado em uma thread)
				k = i;
				for(l = 0; l < TAB_LARG; l++){
					seqLinha[l] = tab[k][l];
				}
				
				// Percorre a coluna (Pode ser jogado em uma thread)
				l = j;
				for(k = 0; k < TAB_LARG; k++){
					seqColuna[k] = tab[k][l];
				}
				
				// Percorre o quadrado (Pode ser jogado em uma thread)
				inicioLinha = ((i/3)*3);
				inicioColuna = ((j/3)*3);
				for(m = inicioLinha, k = 0; m < (inicioLinha + 3); m++, k++){
					for(n = inicioColuna, l = 0; n < (inicioColuna + 3); n++, l++){
						seqQuadrado[(k*3)+l] = tab[m][n];
					}
				} 
				
				for(k = 0; k < MAX_NUM; k++){
					existeLinha = verificaExistencia(seqLinha, k+49);
					existeColuna = verificaExistencia(seqColuna, k+49);
					existeQuadrado = verificaExistencia(seqQuadrado, k+49);
					
					if(existeLinha == 0 && existeColuna == 0 && existeQuadrado == 0){
						maxValue++;
						possibilidades[numDicas][maxValue] = k+49;
					}
				}
				
				if(maxValue > 0){
					possibilidades[numDicas][0] = maxValue;
					numDicas++;
				} // Fim if
			} //Fim if
		} //Fim for
	} //Fim for
	
	k = 0;
	for(i = 0; i < TAB_ALT; i++){
		for(j = 0; j < TAB_LARG; j++){
			if(tab[i][j] == 'X'){
				printf("(");
				for(l = 1; l <= possibilidades[k][0]; l++){
					printf("%c", possibilidades[k][l]);
				}
				printf(")    ");
				k++;
			} else {
				printf("%c    ", tab[i][j]);
			}
		} // Fim for
		printf("\n");
	} //Fim for
	
	return 1;
	
} //Fim função dicas

int verificaExistencia(char *sequencia, int searchValue){
	int i;
	char charSearchValue = searchValue;
	for(i = 0; i < MAX_NUM; i++){
		if(sequencia[i] == charSearchValue){
			return 1;
		}
	}
	
	return 0;
}
