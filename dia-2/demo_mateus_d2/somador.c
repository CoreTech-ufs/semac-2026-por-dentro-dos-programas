#include <stdio.h>


int main() {
    int a = 10;
    int b = 20;

    int resultado = somador(a, b);
    printf("%i", resultado);
    
    return 0;
}

int somador (int x, int y) {
    int soma = x + y;
    return soma;
}