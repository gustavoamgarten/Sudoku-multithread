#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "completa.h"
#include "dicas.h"
#include "verificacao.h"

#define TAB_LARG 9
#define TAB_ALT 9

#define MAX_CASAS 81
#define MAX_NUM 9

// Função para procurar as dicas no tabuleiro fornecido em uma matriz char 9x9.
int completa(char tab[TAB_LARG][TAB_ALT], int linhaInicial, int colunaInicial){
	
	if(linhaInicial == (TAB_LARG - 1) && colunaInicial == (TAB_ALT - 1) && tab[linhaInicial][colunaInicial] != 'X'){
		return 1;
	}
	
	int i, j, k, l, m, n; // Variáveis contadoras
	
	char copiaTabOriginal[TAB_ALT][TAB_LARG];
	
	char possibilidades[MAX_CASAS][MAX_NUM + 1]; // Vetor que contém sequências de números possíveis para cada campo em que foi encontrado um X.
	int numDicas = 0; // Contador do número de campos que requerem dicas.
	
	// Variáveis que armazenam o retorno das funções que verificam se algum número existe na linha, coluna ou quadrado indicado.
	int *existeLinha;
	int *existeColuna;
	int *existeQuadrado;
	
	int completou = 0; // Contador que indica se o uso de tal numero completou o restante do tabuleiro.
	
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
						tab[i][j] = k + 49;
						completou = completa(tab, i, j);
						if(completou == 0){
							tab[i][j] = 'X';
						} else {
							//k = MAX_NUM; // Sai do for
							return 1;
						} 
					}
				} // Fim for
				
				// Caso nenhum número se encaixe
				return 0;
				
			} //Fim if
		} //Fim for
	} //Fim for
	
	return 1;
	
} //Fim função completa
