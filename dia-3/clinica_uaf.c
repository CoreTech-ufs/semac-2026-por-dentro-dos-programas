#include <stdio.h>
#include <stdlib.h>

int* validar_leituras(int *buf, int qtd) {
    for (int i = 0; i < qtd; i++) {
        if (buf[i] < 0) {
            free(buf); // Libera no caminho de erro, mas devolve o endereço antigo
            return buf;
        }
    }
    return buf;
}

int main(void) {
    int *sensores = (int*) malloc(3 * sizeof(int));
    if (sensores == NULL) return 1;

    sensores[0] = 22;
    sensores[1] = -1; // Força o caminho de erro
    sensores[2] = 25;

    sensores = validar_leituras(sensores, 3);

    // Uso após liberação (Use-After-Free): leitura de bloco já devolvido à Heap
    printf("Leitura inicial: %d\n", sensores[0]);
    return 0;
}