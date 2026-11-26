/*
* Programa que demonstra desvio de fluxo por corrupção de memória na entrada.
*
* Criado por: João Vinícius
* Compilação: gcc exemplo_desvio_execucao2.c -o exemplo_desvio_execucao2.elf
* Execução: ./exemplo_desvio_execucao2.elf
*/

#include <stdio.h>
#include <stdlib.h>

#define TAM_PALAVRA 10

typedef struct {
    char palavra[TAM_PALAVRA];
    char repeticoes[3];
} Dados;

int main() {
    Dados d;

    // Corrupção proposital da memória
    const int TAM_INCORRETO = TAM_PALAVRA + 3;

    printf("Digite uma palavra (10 caracteres) e a qtd de repeticoes: ");
    fgets(d.palavra, TAM_INCORRETO, stdin);

    int repeticoes = atoi(d.repeticoes);

    for (int i = 0; i < repeticoes; i++) {
        printf("%s\n", d.palavra);
    }

    return 0;
}