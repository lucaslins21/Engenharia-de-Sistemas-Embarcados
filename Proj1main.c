#include <REG51.H>

void main() {
    while (1) {
			
				//verifica o bit 1 de P2 é igual a 1 
        if (P2 & 0x02) {
            //copia os 4 bits mais significativos de P0 para P1
            P1 = (P1 & 0x0F) | (P0 & 0xF0);
        } else {
            //zera os 4 bits mais significativos de P1
            P1 &= 0x0F;
        }
			
        //verifica o bit 0 de P2 é igual a 1 
        if (P2 & 0x01) {
            //copia os 4 bits menos significativos de P0 para P1
            P1 = (P1 & 0xF0) | (P0 & 0x0F);
        } else {
            //zera os 4 bits menos significativos de P1
            P1 &= 0xF0;
        }
    }
}
