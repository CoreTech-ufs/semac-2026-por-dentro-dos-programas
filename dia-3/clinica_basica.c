/*
* Código de clinica básica
*
* Criado por: Rafael Coelho
* Compilação: gcc -Wall -Wextra -d clinica_basica.c -o clinica_basica
* Execução: ./clinica_basica
*/

#include <stdio.h>
#include <stdlib.h>

int somar_amostras(int qtd) {
    int *amostras = (int*) malloc(qtd * sizeof(int));
    if (amostras == NULL) return -1;

    for (int i = 0; i <= qtd; i++) {
        amostras[i] = (i + 1) * 10;
    }

    int total = 0;
    for (int i = 0; i < qtd; i++) {
        total += amostras[i];
    }

    return total;
}

int main(void) {
    int resultado = somar_amostras(4);
    printf("Total: %d\n", resultado);
    return 0;
}
