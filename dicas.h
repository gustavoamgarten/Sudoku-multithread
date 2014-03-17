#ifndef DICAS_H
#define DICAS_H

// ##############################
// Estruturas necessárias para passar mais de uma variável para uma função utilizada em uma thread.
// ##############################

typedef struct argPercorre {
	int i;
	char (*tab)[9];
} ArgPercorre;

typedef struct argPercorreQuadrado {
	int inicioLinha;
	int inicioColuna;
	char (*tab)[9];
} ArgPercorreQuadrado;

typedef struct argVerificaSequencia {
	int searchValue;
	char *sequencia;
} ArgVerificaSequencia;

typedef struct argVerificacao {
	int searchValue;
	int posElemento;
	char *sequencia;
} ArgVerificacao;

// ##############################
// Fim estruturas
// ##############################

int dicas(char tab[9][9]);
void *percorre_linha(void *arg);
void *percorre_coluna(void *arg);
void *percorre_quadrado(void *arg);
void *verificaExistencia(void *arg);

#endif
