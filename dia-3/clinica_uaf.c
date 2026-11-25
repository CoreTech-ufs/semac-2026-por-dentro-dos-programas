#include <stdio.h>
#include <stdlib.h>

int* validar_leituras(int *buf, int qtd) {
    for (int i = 0; i < qtd; i++) {
        if (buf[i] < 0) {
            free(buf);
            return buf;
        }
    }
    return buf;
}

int main(void) {
    int *sensores = (int*) malloc(3 * sizeof(int));
    if (sensores == NULL) return 1;

    sensores[0] = 22;
    sensores[1] = -1;
    sensores[2] = 25;

    sensores = validar_leituras(sensores, 3);

    printf("Leitura inicial: %d\n", sensores[0]);
    return 0;
}