#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "dicas.h"

#define TAB_LARG 9
#define TAB_ALT 9

#define MAX_CASAS 81
#define MAX_NUM 9


// ##############################
// Funções chamadas pelas threads.
// ##############################

// Função para percorrer a linha do campo atual.
void *percorre_linha(void *arg){
	ArgPercorre argumento;
	argumento = *(ArgPercorre *)arg;
	
	int k = argumento.i;
	int l;
	char *seqLinha = (char *) malloc(9*sizeof(char));
	char (*tab)[9] = argumento.tab;
	
	for(l = 0; l < TAB_LARG; l++){
		seqLinha[l] = tab[k][l];
	}
	
	return seqLinha;
}

// Função para percorrer a coluna do campo atual.
void *percorre_coluna(void *arg){
	ArgPercorre argumento;
	argumento = *(ArgPercorre *)arg;
	
	int k = argumento.i;
	int l;
	char *seqColuna = (char *) malloc(9*sizeof(char));
	char (*tab)[9] = argumento.tab;
	
	for(l = 0; l < TAB_LARG; l++){
		seqColuna[l] = tab[l][k];
	}
	
	return seqColuna;
}

// Função para percorrer o quadrado do campo atual.
void *percorre_quadrado(void *arg){
	ArgPercorreQuadrado argumento;
	argumento = *(ArgPercorreQuadrado *)arg;
	
	int m, n, k, l;
	char *seqQuadrado = (char *) malloc(9*sizeof(char));
	char (*tab)[9] = argumento.tab;
	
	for(m = argumento.inicioLinha, k = 0; m < (argumento.inicioLinha + 3); m++, k++){
		for(n = argumento.inicioColuna, l = 0; n < (argumento.inicioColuna + 3); n++, l++){
			seqQuadrado[(k*3)+l] = tab[m][n];
		}
	}
	
	return seqQuadrado;
}

// Função que verifica a existencia de um numero em uma sequencia (array).
//void *verificaExistencia(char *sequencia, int searchValue){
void *verificaExistencia(void *arg){
	ArgVerificaSequencia argumento = *(ArgVerificaSequencia *)arg;
	int i;
	int *returnValue = (int *) malloc(sizeof(int));
	char charSearchValue = argumento.searchValue;
	for(i = 0; i < MAX_NUM; i++){
		if(argumento.sequencia[i] == charSearchValue){
			*returnValue = 1;
			return returnValue;
		}
	}
	
	*returnValue = 0;
	return returnValue;
}

// ##############################
// Fim das funções chamadas pelas threads.
// ##############################

// Função para procurar as dicas no tabuleiro fornecido em uma matriz char 9x9.
int dicas(char tab[TAB_LARG][TAB_ALT]){
	
	int i, j, k, l, m, n; // Variáveis contadoras
	
	char possibilidades[MAX_CASAS][MAX_NUM + 1]; // Vetor que contém sequências de números possíveis para cada campo em que foi encontrado um X.
	int numDicas = 0; // Contador do número de campos que requerem dicas.
	
	// Variáveis que armazenam o retorno das funções que verificam se algum número existe na linha, coluna ou quadrado indicado.
	int *existeLinha;
	int *existeColuna;
	int *existeQuadrado;
	
	int maxValue = 0; // Contador que indica a quantidade de numeros possíveis em cada campo.
	
	int inicioLinha, inicioColuna; // Contadores que indicam o ponto de inicio de um quadrado referente a um elemento do tabuleiro.
	
	// Threads que serão utilizadas.
	pthread_t thread[3];
	
	// Vetores que armazenam as sequencias contidas na linha, coluna e quadrado de uma posição do tabuleiro.
	char *seqLinha;
	char *seqColuna;
	char *seqQuadrado;
	
	// Variáveis que armazenam os argumentos necessários para as funções chamadas nas threads.
	ArgPercorre *argLinha = (ArgPercorre *) malloc(sizeof(ArgPercorre));
	ArgPercorre *argColuna = (ArgPercorre *) malloc(sizeof(ArgPercorre));
	ArgPercorreQuadrado *argQuadrado = (ArgPercorreQuadrado *) malloc(sizeof(ArgPercorreQuadrado)); 
	ArgVerificaSequencia *argVerifica = (ArgVerificaSequencia *) malloc(3*sizeof(ArgVerificaSequencia)); 
	
	// Percorre o tabuleiro procurando os campos que contém um X
	for(i = 0; i < TAB_LARG; i++) {
		for(j = 0; j < TAB_ALT; j++){
			if(tab[i][j] == 'X') {
				
				maxValue = 0;
				
				// Percorre a linha em uma thread própria.
				argLinha->i = i;
				argLinha->tab = tab;
				pthread_create(&(thread[0]), NULL, percorre_linha, (void *)argLinha);
				
				// Percorre a coluna em uma thread própria.				
				argColuna->i = j;
				argColuna->tab = tab;
				pthread_create(&(thread[1]), NULL, percorre_coluna, (void *)argColuna);
				
				// Percorre o quadrado em uma thread própria.
				argQuadrado->inicioLinha = ((i/3)*3);
				argQuadrado->inicioColuna = ((j/3)*3);
				argQuadrado->tab = tab;
				pthread_create(&(thread[2]), NULL, percorre_quadrado, (void *)argQuadrado); 
				
				// Espera percorrer todos os campos necessarios e armazena as sequencias nas respectivas variáveis.
				pthread_join(thread[0], (void**)&seqLinha);
				pthread_join(thread[1], (void**)&seqColuna);
				pthread_join(thread[2], (void**)&seqQuadrado); 
				
				for(k = 0; k < MAX_NUM; k++){
					// Verifica a existência do número k, na respectiva linha
					argVerifica[0].searchValue = k+49;
					argVerifica[0].sequencia = seqLinha;
					pthread_create(&(thread[0]), NULL, verificaExistencia, (void *)&argVerifica[0]);
					
					// Verifica a existência do número k, na respectiva coluna
					argVerifica[1].searchValue = k+49;
					argVerifica[1].sequencia = seqColuna;
					pthread_create(&(thread[1]), NULL, verificaExistencia, (void *)&argVerifica[1]);
					
					// Verifica a existência do número k, no respectivo quadrado
					argVerifica[2].searchValue = k+49;
					argVerifica[2].sequencia = seqQuadrado;
					pthread_create(&(thread[2]), NULL, verificaExistencia, (void *)&argVerifica[2]);
					
					// Espera percorrer todos os campos necessarios e armazena as sequencias nas respectivas variáveis.
					pthread_join(thread[0], (void*)&existeLinha);
					pthread_join(thread[1], (void*)&existeColuna);
					pthread_join(thread[2], (void*)&existeQuadrado); 
					
					if(*existeLinha == 0 && *existeColuna == 0 && *existeQuadrado == 0){
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
	
	// Percorre o tabuleiro novamente, indicando as dicas nos respectivos campos com X.
	printf("Dicas: \n\n");
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
