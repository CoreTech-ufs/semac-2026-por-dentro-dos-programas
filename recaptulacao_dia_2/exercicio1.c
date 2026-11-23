#include <stdio.h>

static int media = 0;

void funcao(int *vetor_passado,int tamanho) {

    for (int i = 0; i < tamanho; i++) {
        media += vetor_passado[i];
        printf("ITERACAO DA SOMA[%d]:%d.\n",i,media);
    }
        media = media / tamanho ;
        printf("Valor da media:%d.\n",media);
    }

int main() {
    printf("Valor inicial da variavel media:%d\n",media);
    int vetor[5] = {2, 3, 4, 5, 6}; // Soma = 20, Média = 4
    funcao(vetor,sizeof(vetor)/sizeof(int));
    return 0;
}

/*Lista de comandos uteis

* COMPILACAO REGULAR: gcc -o executavel exercicioN.c
* EXECUCAO REGULAR: ./executavel 

* COMPILACAO COM GDB: gcc -g exercicioN.c -o executavel
* EXECUCAO CHAD: GDB ./executavel

**SECAO GDB:
    -> "break checkpoint" (sugestao de checkpoint: "main" e "funcao_chamada_no_exercicio") 
    -> "run" (inicio da execucao, sugestao "layout src" antes do "run" para visualizacao da depuracao)
    -> "next" (avancar na depuracao)
    -> "ptype vetor"
    -> "ptype media"
    -> "print sizeof(&vetor)"
    -> "print &vetor"
*/