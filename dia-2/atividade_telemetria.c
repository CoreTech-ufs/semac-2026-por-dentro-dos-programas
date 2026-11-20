/*
* Esse código é responsável pela telemetria de uma aeronave tripulada.
* Os dados são processados localmente e um pacote é enviado via rádio a cada X segundos.
* 
* Tarefa: Engenheiros de teste relataram falhas operacionais graves e inconsistência nos 
* dados recebidos, é seu papel analisar o código do firmware e corrigir erros.
*
* Criado por: João Vinícius
* Compilação: 
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <math.h>

#define TAM_HISTORICO 10
#define FREQ_ENVIO 1 // Hertz

enum { X, Y, Z };

typedef struct {
    uint64_t num_seq; // Número de pacote
    float altitude;   // Altitude (metros)
    float acel[3];    // Acelerômetro (g)
    float coord[2];   // Coordenadas geográficas
} PacoteAeronave;

PacoteAeronave* criar_pacote() {
    PacoteAeronave* pacote = (PacoteAeronave*)malloc(sizeof(PacoteAeronave));

    return pacote;
}

uint64_t obter_numero_sequencia() {
    static uint64_t num_seq = 0;
    return num_seq++;
}

void processar_dados(PacoteAeronave* pacote) {
    const float ALTITUDE_MINIMA = 8000.0f;

    // Detecção de limite de altitude
    if (pacote->altitude < ALTITUDE_MINIMA) {
        printf("**ALERTA: Aeronave abaixo de %f m.\n", ALTITUDE_MINIMA);
    }

    // Detecção de queda
    float soma = 0.0f;

    for (uint8_t i = 0; i < 3; i++) {
        soma += powf(pacote->acel[i], 2);
    }

    float magnitude = sqrt(soma);
        
    if (magnitude <= 1.5f) {
        printf("**ALERTA: Possível queda livre");
    }
}

void obter_dados_sensores(PacoteAeronave* pacote) {
    float r = (float)rand() / RAND_MAX;

    pacote->altitude = 12000.0f + 100.0f * r;

    pacote->acel[X] = 0.0f + 0.5f * r;
    pacote->acel[Y] = 0.0f + 0.5f * r;
    pacote->acel[Z] = 9.81f + 0.8f * r;

    pacote->coord[X] = -10.9250f + 0.001f * pacote->num_seq + 0.0001f * r;
    pacote->coord[Y] = -37.1000f + 0.0001f * r;
}

// void atualizar_historico(PacoteAeronave* h, PacoteAeronave pacote) {
//     // Desloca pacotes antigos para trás
//     for (uint8_t i = TAM_HISTORICO-1; i > 0; i--) h[i] = h[i-1];

//     // Insere novo pacote no início
//     memcpy(&h[0], &pacote, sizeof(PacoteAeronave));
// }

int enviar_pacote(PacoteAeronave* pacote) {
    printf("\nPacote %llu:\n*Altitude: %f m\n*Acelerecao (ms²): %f %f %f\n*Coord: %f° %f°\n",
        pacote->num_seq,
        pacote->altitude,
        pacote->acel[X],
        pacote->acel[Y],
        pacote->acel[Z],
        pacote->coord[X],
        pacote->coord[Y]
    );

    // Lógica de envio...

    return 0;
}

int main() {
    // Histórico contendo últimos pacotes
    PacoteAeronave pacotes_enviados[TAM_HISTORICO] = {0};

    for (uint64_t i = 0 ;; i++) {
        // Preparação dos dados do pacote
        PacoteAeronave* pacote = criar_pacote();
    
        pacote->num_seq = obter_numero_sequencia();
        obter_dados_sensores(pacote);
        processar_dados(pacote);

        // atualizar_historico(pacotes_enviados, *pacote);
        enviar_pacote(pacote);
        free(pacote);

        // Pausa a execução do programa por um certo tempo
        sleep((int)(1.0f/FREQ_ENVIO));
    }

    return 0;
}