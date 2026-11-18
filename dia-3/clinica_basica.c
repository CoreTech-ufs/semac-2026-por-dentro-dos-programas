#include <stdio.h>
#include <stdlib.h>

int somar_amostras(int qtd) {
    int *amostras = (int*) malloc(qtd * sizeof(int));
    if (amostras == NULL) return -1;

    // ERRO 1 (Limite): '<=' escreve 1 inteiro além do bloco alocado
    for (int i = 0; i <= qtd; i++) {
        amostras[i] = (i + 1) * 10;
    }

    int total = 0;
    for (int i = 0; i < qtd; i++) {
        total += amostras[i];
    }

    // ERRO 2 (Responsabilidade): retorna sem liberar 'amostras'
    return total;
}

int main(void) {
    int resultado = somar_amostras(4);
    printf("Total: %d\n", resultado);
    return 0;
}
