/*
* Código de exemplo que demonstra o tempo de vida de variáveis.
* Criado por: João Vinícius
* Compilação: gcc exemplo_lifetime.c -o exemplo_lifetime.elf
* Execução: ./exemplo_lifetime.elf
*/

#include <stdio.h>

int* criar_numero() {
    int num = 10;

    printf("Valor de num (função): %d\n", num);

    return &num;
}

int main() {
    int* num = criar_numero();

    // Imprime valor da variável criada pela função
    printf("Valor de num (main): %d\n", num);

    return 0;
}