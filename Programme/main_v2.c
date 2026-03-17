#include <xc.h>
#include <stdint.h>

#pragma config OSC = IntRC   // Oscillateur interne
#pragma config WDT = OFF     // Watchdog éteint
#pragma config CP = ON       // Protection de code activée
#pragma config MCLRE = OFF   // GP3 est une entrée digitale (indispensable)

#define _XTAL_FREQ 4000000   // 4MHz

// Variable globale pour l'aléatoire
uint8_t lfsr_seed = 0x92; 

// --- FONCTION ALÉATOIRE LFSR ---
void update_lfsr() {
    if (lfsr_seed & 0x01) {
        lfsr_seed = (lfsr_seed >> 1) ^ 0xB8;
    } else {
        lfsr_seed = (lfsr_seed >> 1);
    }
}

// --- FONCTION AFFICHAGE ---
void afficher_de(uint8_t n) {
    GPIO = 0;
    switch(n) {
        case 1: GPIO = 0b000001; break; // Exemple : GP0 seul
        case 2: GPIO = 0b000010; break; // Exemple : GP1
        case 3: GPIO = 0b000011; break; // GP0 + GP1
        case 4: GPIO = 0b010010; break; // GP1 + GP4
        case 5: GPIO = 0b010011; break; // GP0 + GP1 + GP4
        case 6: GPIO = 0b010110; break; // GP1 + GP2 + GP4
        default: GPIO = 0;
    }
}

void main(void) {
    // Configuration des Pins : GP3 en entrée, les autres en sortie
    TRIS = 0b001000; 
    
    // Configuration du réveil sur changement d'état (Wake-up on Pin Change)
    // Sur le 12F508, c'est le bit 7 du registre OPTION qui doit être à 0
    OPTION = 0b01111111; 

    while(1) {
        // 1. Éteindre les LEDs et se mettre en veille
        GPIO = 0;
        SLEEP(); // Le PIC s'arrête ici jusqu'à une secousse sur GP3

        // 2. RÉVEIL : On mélange l'aléatoire tant que ça secoue
        for(uint16_t i = 0; i < 1000; i++) {
            update_lfsr();
            // Si le capteur bouge encore, on continue de mélanger
            if(GP3 == 0) i = 0; 
        }

        // 3. CALCUL DU RÉSULTAT (1 à 6)
        uint8_t resultat = (lfsr_seed % 6) + 1;

        // 4. AFFICHAGE pendant 5 secondes
        afficher_de(resultat);
        __delay_ms(5000);
        
        // Le cycle recommence et retourne au SLEEP
    }
}
