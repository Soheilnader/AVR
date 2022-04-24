
#include <mega32.h>
#include "lcd.h"
#include <delay.h>


void main(void)
{

DDRC=0xFF;
DDRD=0xFF;

PORTC=0;
PORTD=0;



lcd_init();
lcd_putchar('A');
delay_ms(1000);
lcd_clear();
lcd_gotoxy(1,0);
lcd_putchar('A');
delay_ms(1000);
lcd_clear();
lcd_gotoxy(1,5);
lcd_puts("salam!");
delay_ms(1000);
lcd_clear();
lcd_puts("salam Soheil");
lcd_gotoxy(1,0);
lcd_puts("Nadernezhad");
delay_ms(1000);
lcd_clear();
lcd_puts("GARD");
delay_ms(1000);
lcd_clear();
lcd_gotoxy(0,10);
lcd_puts("GARD");
delay_ms(1000);
lcd_clear();
lcd_gotoxy(1,0);
lcd_puts("GARD");
delay_ms(1000);
lcd_clear();
lcd_gotoxy(1,10);
lcd_puts("GARD");
delay_ms(1000);
lcd_clear();
lcd_puts("Salam ostad");
lcd_gotoxy(1,0);
lcd_puts("Najafi");
delay_ms(1000);


    while(1){
    
    }
}
