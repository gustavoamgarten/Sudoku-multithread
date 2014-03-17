#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "dicas.h"

#define TAB_LARG 9
#define TAB_ALT 9

#define MAX_CASAS 81
#define MAX_NUM 9

// Função que verifica a existencia de um numero em uma sequencia (array).
//void *verificaExistencia(char *sequencia, int searchValue){
void *verificaExistenciaIncluindoCampo(void *arg){
	ArgVerificacao argumento = *(ArgVerificacao *)arg;
	int i, once = 0;
	int *returnValue = (int *) malloc(sizeof(int));
	char charSearchValue = argumento.searchValue;
	for(i = 0; i < MAX_NUM; i++){
		if(argumento.sequencia[i] == charSearchValue){
			if(once == 1){
				*returnValue = 1;
				return returnValue;
			}
			once = 1;
		}
	}
	
	*returnValue = 0;
	return returnValue;
}

// Função para procurar as dicas no tabuleiro fornecido em uma matriz char 9x9.
int verifica(char tab[TAB_LARG][TAB_ALT]){
	
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
	ArgVerificacao *argVerifica = (ArgVerificacao *) malloc(3*sizeof(ArgVerificacao));
	
	int posSeqLinha;
	int posSeqColuna;
	int posSeqQuadrado; 
	
	// Percorre o tabuleiro procurando os campos que contém um X
	for(i = 0; i < TAB_LARG; i++) {
		for(j = 0; j < TAB_ALT; j++){
			if(tab[i][j] != 'X'){	
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
				
				//for(k = 0; k < MAX_NUM 
				
				// Verifica a existência do número, na respectiva linha
				argVerifica[0].searchValue = tab[i][j];
				argVerifica[0].sequencia = seqLinha;
				pthread_create(&(thread[0]), NULL, verificaExistenciaIncluindoCampo, (void *)&argVerifica[0]);
				
				// Verifica a existência do número, na respectiva coluna
				argVerifica[1].searchValue = tab[i][j];
				argVerifica[1].sequencia = seqColuna;
				pthread_create(&(thread[1]), NULL, verificaExistenciaIncluindoCampo, (void *)&argVerifica[1]);
				
				// Verifica a existência do número, no respectivo quadrado
				argVerifica[2].searchValue = tab[i][j];
				argVerifica[2].sequencia = seqQuadrado;
				pthread_create(&(thread[2]), NULL, verificaExistenciaIncluindoCampo, (void *)&argVerifica[2]);
				
				// Espera percorrer todos os campos necessarios e armazena as sequencias nas respectivas variáveis.
				pthread_join(thread[0], (void*)&existeLinha);
				pthread_join(thread[1], (void*)&existeColuna);
				pthread_join(thread[2], (void*)&existeQuadrado); 
				
				if(*existeLinha != 0 || *existeColuna != 0 || *existeQuadrado != 0){
					if(*existeLinha != 0)
						printf("A linha %d contém mais de uma ocorrência de %c.\n", argLinha->i + 1, tab[i][j]);
					else if(*existeColuna != 0)
						printf("A coluna %d contém mais de uma ocorrência de %c.\n", argColuna->i + 1, tab[i][j]);
					else if(*existeQuadrado != 0)
						printf("O quadrado que se inicio na linha %d e coluna %d contém mais de uma ocorrência de %c.\n", argQuadrado->inicioLinha, argQuadrado->inicioColuna, tab[i][j]);
						
					return 0;
				}
			
			} // Fim if
		} //Fim for
	} //Fim for
	
	return 1;
	
} //Fim função verifica
