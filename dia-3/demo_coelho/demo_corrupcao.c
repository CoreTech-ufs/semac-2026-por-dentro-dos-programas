/*
* Código de demonstração de erro
*
* Criado por: Rafael Coelho
* Compilação: gcc -g -O0 demo_corrupcao.c -o demo_corrupcao
* Execução: ./demo_corrupcao
*
* Saída esperada:
* Antes:  modo_diagnostico = 0
* Depois: modo_diagnostico = 1
*/

#include <stdio.h>

typedef struct {
    int leituras[3];      // índices: 0, 1, 2
    int modo_diagnostico; // variável vizinha
} PainelSensor;

int main(void) {
    PainelSensor p = {{10, 20, 30}, 0};

    printf("Antes:  %d\n", p.modo_diagnostico);
    p.leituras[3] = 1; // escrita fora do limite
    printf("Depois: %d\n", p.modo_diagnostico);

    return 0;
}