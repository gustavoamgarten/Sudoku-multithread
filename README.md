Sudoku-multithread
==================

MC504 - Trabalho 1

Gustavo Amgarten de Lêdo    RA: 139490
Lucas de Souza e Silva    RA: 140765

Modo de uso:

O programa é dividido em 3 módulos: Verificação (verificacao.c), Dicas (dicas.c) e Preenchimento (completa.c).

O arquivo principal (sudoku.c) faz utilização desses módulos.

No arquivo principal (sudoku.c) deve ser declarado uma matriz que representa o tabuleiro do Sudoku.

A função de verificação e de dicas recebem de parãmetro apenas a matriz que representa o tabuleiro.

A função de preenchimento recebe, além do tabuleiro, a linha e a coluna que deve começar a preencher.


A estratégia multi-thread utilizada, é composta básicamente por procurar conlitos em uma linha, coluna ou quadrado em threads diferentes (uma para cada região).
A vantagem é que essas buscas ocorrem ao mesmo tempo, sendo que uma não precisa esperar a outra terminar para realizar seu trabalho, resultando em uma melhor eficiência.

Por outro lado, foi necessária a criação de estruturas e variáveis adicionais.
