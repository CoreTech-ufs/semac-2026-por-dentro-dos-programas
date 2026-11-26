/*
* Código simples de telemetria
*
* Criado por: Rafael Coelho
* Compilação: gcc -g -O0 -Wall -Wextra mini_telemetria.c -o mini_telemetria
* Execução (c/ GDB): gdb ./mini_telemetria

* Parte 1:
* break processar
* next
* print leituras

* Saída esperada:
* Antes:  modo_diagnostico = 0
* Depois: modo_diagnostico = 1
*/

#include <stdio.h>
#include <stdlib.h>

void processar(void) {
    int *leituras = malloc(4 * sizeof(int));

    if (leituras == NULL)
        return;

    for (int i = 0; i < 4; i++)
        leituras[i] = i * 10;

    leituras[4] = 999;

    printf("Última leitura: %d\n", leituras[3]);

    // O que está faltando?
}

int main(void) {
    processar();
    return 0;
}
