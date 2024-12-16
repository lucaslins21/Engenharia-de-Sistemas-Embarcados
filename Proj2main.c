#include <8051.h> // Biblioteca padrão para o microcontrolador 8051

// Máscaras para manipulação de bits
#define P0H_MASK 0xF0 // Máscara para os 4 bits mais significativos de P0
#define P0L_MASK 0x0F // Máscara para os 4 bits menos significativos de P0
#define P1H_MASK 0xF0 // Máscara para os 4 bits mais significativos de P1
#define P1L_MASK 0x0F // Máscara para os 4 bits menos significativos de P1

unsigned int i = 0;
sfr P0 = 0x80; // Porta 0
sfr P1 = 0x90; // Porta 1
sfr P2 = 0xA0; // Porta 2

// Função para tratar evento do bit 1 de P2 (atribuir bits mais significativos)
void funcaoA() {
    static char estadoA = 0;

    switch (estadoA) {
        case 0: // Estado inicial
            if ((P2 & 0x02) == 0x02) { // Verifica se o bit 1 de P2 mudou para 1
                P1 = (P1 & P1L_MASK) | (P0 & P0H_MASK); // Atualiza APENAS os 4 bits mais significativos
                estadoA = 1; // Transição para o próximo estado
            }
            break;

        case 1: // Estado de atraso
            for (i = 0; i < 12000; i++); // Delay via software (ajuste conforme necessário)
            P1 &= P1L_MASK; // Zera APENAS os 4 bits mais significativos
            estadoA = 0; // Retorna ao estado inicial
            break;

        default:
            estadoA = 0; // Estado padrão para evitar falhas
            break;
    }
}

// Função para tratar evento do bit 0 de P2 (atribuir bits menos significativos)
void funcaoB() {
    static char estadoB = 0;

    switch (estadoB) {
        case 0: // Estado inicial
            if ((P2 & 0x01) == 0x01) { // Verifica se o bit 0 de P2 mudou para 1
                P1 = (P1 & P1H_MASK) | (P0 & P0L_MASK); // Atualiza APENAS os 4 bits menos significativos
                estadoB = 1; // Transição para o próximo estado
            }
            break;

        case 1: // Estado de atraso
            for (i = 0; i < 12000; i++); // Delay via software (ajuste conforme necessário)
            P1 &= P1H_MASK; // Zera APENAS os 4 bits menos significativos
            estadoB = 0; // Retorna ao estado inicial
            break;

        default:
            estadoB = 0; // Estado padrão para evitar falhas
            break;
    }
}

void main() {
    while (1) {
        funcaoA(); // Trata eventos do bit 1 de P2
        funcaoB(); // Trata eventos do bit 0 de P2
    }
}
