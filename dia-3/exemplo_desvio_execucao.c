#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#define TAM_ARR 5

typedef struct {
    uint32_t offsets[TAM_ARR];
    uint32_t leituras_sensor[TAM_ARR];
    bool calibrado;
} SensorRobo;

void inicializar_sensor(SensorRobo* s) {
    s->calibrado = false;
}

void calibrar_sensor(SensorRobo* s) {
    for (uint32_t i = 0; i <= TAM_ARR; i++) {
        s->offsets[i] = s->leituras_sensor[i];
    }

    printf("Sensor calibrado.\n");
}

void iniciar_operação(SensorRobo* s) {
    printf("Operação iniciada. Calibrado=%d\n", s->calibrado);
}

int main() {
    SensorRobo sensor;

    inicializar_sensor(&sensor);

    // Obtendo valores iniciais
    for (uint32_t i = 0; i <= TAM_ARR; i++) {
        sensor.leituras_sensor[i] = (uint32_t)(6 * (float)rand() / RAND_MAX);
    }

    // Realizando calibração condicional
    if (!sensor.calibrado) {
        calibrar_sensor(&sensor);
        iniciar_operação(&sensor);
    } else {
        iniciar_operação(&sensor);
    }

    return 0;
}