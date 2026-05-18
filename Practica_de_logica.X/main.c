

// CONFIG1
#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator: Crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown Out Reset Selection bits (BOR enabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.


#define _XTAL_FREQ 4000000 // velocidad del cristal oscilador
#include <xc.h>

#include <stdio.h> // librería agregada
#include <stdbool.h> 

void main(void) {
    ANSELH = 0;
    //definimos los pines
    TRISC = 0;
    TRISBbits.TRISB0 = 1;
    TRISBbits.TRISB1 = 1;
    TRISBbits.TRISB2 = 1;
    PORTC = 0;
    
    //introducimos las variables
    int velocidad = 1;
    int posicion = 0;
    bool izquierda = false;
    bool activo = false;
    //anti rebote 
    do {
        if (PORTBbits.RB0 == 1) {
            while (PORTBbits.RB0 == 1);
             activo = !activo;
        }
            
          
        if (PORTBbits.RB1 == 1){
            while (PORTBbits.RB1 == 1);
            velocidad ++;
            if (velocidad > 3){
                velocidad = 1;
            }
        }
       
        if (PORTBbits.RB2 == 1){
            while (PORTBbits.RB2 == 1);
            if (velocidad > 0){
                velocidad --;
                
            }
                
            }
            switch (velocidad) {
                
                    case 1: 
                        if (izquierda == false && activo ){
                            PORTC = (1 << posicion);
                            __delay_ms (1500);
                            posicion ++;
                            if (posicion > 8){
                                posicion = 0;
                            }
                        }
                        break;
                        
                    case 2: 
                        if (izquierda == false) {
                            PORTC = (1 << posicion);
                            __delay_ms (1000);
                            posicion ++; 
                            if (posicion > 8){
                                posicion = 0;
                            }
                        }
                        break;
                        
                    case 3:
                          if (izquierda == false) {
                            PORTC = (1 << posicion);
                            __delay_ms (500);
                            posicion ++; 
                            if (posicion > 8){
                                posicion = 0;
                            }
                        }
                          break;
            }
        
        
        
        
    } while (1);
    
}
                                                                                    