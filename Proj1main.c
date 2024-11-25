#include <REG51.H>

sbit controle_baixo = P2^0;
sbit controle_alto = P2^1;

void main() {
    unsigned char aux_p1 = 0x01; //Inicializa com 1

    while (1) {
        //verifica se o bit 1 de P2 é igual a 1
        if (controle_alto) {
            //atualiza os 4 bits mais significativos de aux_p1 com os de P0
            aux_p1 = (aux_p1 & 0x0F) | (P0 & 0xF0);
        } else {
            //zera os 4 bits mais significativos de aux_p1
            aux_p1 &= 0x0F;
        }

        //copia o valor calculado para P1
        P1 = aux_p1;

        //verifica se o bit 0 de P2 é igual a 1
        if (controle_baixo) {
            //atualiza os 4 bits menos significativos de aux_p1 com os de P0
            aux_p1 = (aux_p1 & 0xF0) | (P0 & 0x0F);
        } else {
            //zera os 4 bits menos significativos de aux_p1
            aux_p1 &= 0xF0;
        }

        //copia o valor calculado para P1
        P1 = aux_p1;
    }
}
