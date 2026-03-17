#include <stdio.h>
#include <stdlib.h>
#include <xc.h>

#pragma config OSC = IntRC   // Oscillateur interne
#pragma config WDT = OFF     // Watchdog éteint
#pragma config CP = ON       // Protection de code activée
#pragma config MCLRE = OFF   // GP3 est une entrée digitale

#define _XTAL_FREQ 4000000   //4MHz

//GPI0 = Paire LEDs Centrales
//GPI1 = LED Centrale
//GPI2 = Paire LEDs Diag Haut Gauche
//GPI3 = Bouton Detecteur de Mouvements
//GPI4 = Paire LEDs Diag Bas Gauche
//GPI5 = 0V Osciaillateur Interne?? (pas sur)

void main(void) {
    TRIS = 0b00001000;
    OPTION = 0b01000111;
    GPIO = 0b00000000;
    uint8_t randint;
    uint8_t delai;
    
    for(;;){
        for(delai = 0;delai <= 200;){
            if(GPIObits.GP3 == 0){
                delai++;
            }
            randint++;
            __delay_ms(2);
        }
        randint = randint % 6;
        randint++;
        GPIO = 0b00010100; //4
        __delay_ms(100);
        GPIO = 0b00010101; //6
        __delay_ms(100);
        GPIO = 0b00000010; //1
        __delay_ms(200);
        GPIO = 0b00000100; //2
        __delay_ms(200);
        GPIO = 0b00010110; //5
        __delay_ms(300);
        GPIO = 0b00000110; //3
        __delay_ms(300);
        GPIO = 0b00010100; //4
        __delay_ms(400);
        GPIO = 0b00000100; //2
        __delay_ms(400);
        GPIO = 0b00010101; //6
        __delay_ms(500);
        GPIO = 0b00000010; //1
        __delay_ms(500);
        GPIO = 0b00010110; //5
        __delay_ms(600);
        GPIO = 0b00000110; //3
        __delay_ms(600);
        GPIO = 0b00010101; //6
        __delay_ms(800);
        if(randint == 1){
            randint = 0b00000010;
        }else if(randint == 2){
            randint = 0b00000100;
        }else if(randint == 3){
            randint = 0b00000110;
        }else if(randint == 4){
            randint = 0b00010100;
        }else if(randint == 5){
            randint = 0b00010110;
        }else{
            randint = 0b00010101;
        }
        GPIO = randint;
        __delay_ms(4000);
        GPIO = 0b00000000;
        __delay_ms(200);
        GPIO = randint;
        __delay_ms(200);
        GPIO = 0b00000000;
        __delay_ms(200);
        GPIO = randint;
        __delay_ms(200);
        GPIO = 0b00000000;
        __delay_ms(200);
        GPIO = randint;
        __delay_ms(200);
        GPIO = 0b00000000;
        __delay_ms(200);
    }
}
