#include <stdio.h>

typedef struct {
    char buffer_publico[9];   //  DADO PÚBLICO
    char dado_interno[20];    // REGIÃO ADJACENTE SIGILOSA
} FRAME;

void leitura (char *str, int N){  
    for (int i = 0 ; i < N ; i++){
        if(i >= 9){                     //Adição de camada verificadora 
            printf("\nAcesso a regiao nao permitida!");
            break;
        }
        else
        printf("%c",str[i]);
}
printf("\n");
}

int main(){

    FRAME frame = {
        .buffer_publico = "OLA_MUNDO",       
        .dado_interno   = "SENHA_SECRETA_HAHAHA" 
    };

leitura(frame.buffer_publico,30);

}



