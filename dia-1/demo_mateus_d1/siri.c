#include <stdio.h>
#include "siri.h"

void desenhar_garras(void) {
    printf("          _               _\n");
    printf("        /  |             |  \\\n");
    printf("       |  /               \\  |\n");
    printf("       | |   _         _   | |\n");
    printf("        \\ \\_/ \\       / \\_/ /\n");
    printf("         \\____/       \\____/\n");
}

void desenhar_corpo(void) {
    printf("            \\   _   _   /\n");
    printf("             '-'o'-'o'-'\n");
    printf("           .-'---------'-.\n");
    printf("         /'               '\\\n");
    printf("     ___/  .-------------.  \\___\n");
    printf("    /  /  /               \\  \\  \\\n");
    printf("   /  /  |                 |  \\  \\\n");
    printf("   ^  ^   \\               /   ^  ^\n");
}

void imprimir_siri(void) {
    desenhar_garras_2();
    desenhar_corpo();
}

void desenhar_garras_2(void) {
    printf("          _               _\n");
    printf("        /  |             |  \\\n");
    printf("  =====|  /===============\\  |=====\n");
    printf("  =====| |===_=========_===| |=====\n");
    printf("        \\ \\_/ \\       / \\_/ /\n");
    printf("         \\____/       \\____/\n");
}