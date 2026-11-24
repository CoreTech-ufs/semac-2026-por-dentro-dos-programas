#include <stdio.h>

void buscabinaria(int vetor[], int tamanho, int x) {
    int i = 0, f = tamanho , eb = 0, pivo;

    while (i <= f) {
        pivo = (i + f ) / 2;  // Correção no cálculo do pivô 
        if (vetor[pivo] == x) {
            printf("Pertence, e esta na posicao:%d\n",pivo);
            return;
        } else if (x < vetor[pivo]) {
            eb++;
            f = pivo - 1;
        } else {
            eb++;
            i = pivo + 1;
        }
    }
            printf("Nao pertence\n");
            return;

}

int main(){

int vetor[17] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
int buscado1 = 14;

buscabinaria(vetor,17,buscado1);

return 0;
}
