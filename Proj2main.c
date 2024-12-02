#include <REG51.H>

sbit controle_baixo = P2^0; //bit 0 de P2
sbit controle_alto = P2^1;  //bit 1 de P2

void funcaoA() {
    static char estado = 0; //estado inicial
    unsigned char aux_p1 = 0x01; //variável auxiliar inicializada com 1

    switch (estado) {
        case 0: //estado inicial
            if (controle_alto) { //transição detectada
                aux_p1 = (aux_p1 & 0x0F) | (P0 & 0xF0); //copia os 4 MSBs de P0
                P1 = aux_p1; //atualiza P1
                //delay de 1 segundo (via software)
                for (long i = 0; i < 120000; i++);
                estado = 1; //vai para o próximo estado
            }
            break;

        case 1: //próximo estado
            aux_p1 = (aux_p1 & 0x0F) | (P0 & 0xF0); //reatribui os 4 MSBs de P0
            P1 = aux_p1; //atualiza P1
            estado = 0; //retorna ao estado inicial
            break;
    }
}

void funcaoB() {
    static char estado = 0; //estado inicial
    unsigned char aux_p1 = 0x01; //variável auxiliar inicializada com 1

    switch (estado) {
        case 0: //estado inicial
            if (controle_baixo) { //transição detectada
                aux_p1 = (aux_p1 & 0xF0) | (P0 & 0x0F); //copia os 4 LSBs de P0
                P1 = aux_p1; //atualiza P1
                //delay de 1 segundo (via software)
                for (long i = 0; i < 120000; i++);
                estado = 1; //vai para o próximo estado
            }
            break;

        case 1: //próximo estado
            aux_p1 &= 0xF0; //zera os 4 LSBs
            P1 = aux_p1; //atualiza P1
            estado = 0; //retorna ao estado inicial
            break;
    }
}

void main() {
    while (1) {
        funcaoA(); //chama a máquina de estados da transição do bit 1 de P2
        funcaoB(); //chama a máquina de estados da transição do bit 0 de P2
    }
}
