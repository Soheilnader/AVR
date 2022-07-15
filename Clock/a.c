/*******************************************************
This program was created by the
CodeWizardAVR V3.12 Advanced
Automatic Program Generator
© Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : 
Version : 
Date    : 6/29/2022
Author  : 
Company : 
Comments: 


Chip type               : ATmega32
Program type            : Application
AVR Core Clock frequency: 8.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 512
*******************************************************/

#include <mega32.h>
#include <alcd.h>
#include <stdio.h>
#include <delay.h>

#define KEY_SET PIND.3
#define KEY_RIGHT PIND.2
#define KEY_UP PIND.1

int i;
unsigned char sec, min, hour;
char str[17];
enum e_type{
  clock,
  set_hour,
  set_min,
  set_sec}state;

// Timer 0 overflow interrupt service routine
interrupt [TIM0_OVF] void timer0_ovf_isr(void)
{
i++;

}

void main(void)
{
// Declare your local variables here

// Input/Output Ports initialization
// Port A initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRA=(0<<DDA7) | (0<<DDA6) | (0<<DDA5) | (0<<DDA4) | (0<<DDA3) | (0<<DDA2) | (0<<DDA1) | (0<<DDA0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTA=(0<<PORTA7) | (0<<PORTA6) | (0<<PORTA5) | (0<<PORTA4) | (0<<PORTA3) | (0<<PORTA2) | (0<<PORTA1) | (0<<PORTA0);

// Port B initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRB=(0<<DDB7) | (0<<DDB6) | (0<<DDB5) | (0<<DDB4) | (0<<DDB3) | (0<<DDB2) | (0<<DDB1) | (0<<DDB0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTB=(0<<PORTB7) | (0<<PORTB6) | (0<<PORTB5) | (0<<PORTB4) | (0<<PORTB3) | (0<<PORTB2) | (0<<PORTB1) | (0<<PORTB0);

// Port C initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRC=(0<<DDC7) | (0<<DDC6) | (0<<DDC5) | (0<<DDC4) | (0<<DDC3) | (0<<DDC2) | (0<<DDC1) | (0<<DDC0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTC=(0<<PORTC7) | (0<<PORTC6) | (0<<PORTC5) | (0<<PORTC4) | (0<<PORTC3) | (0<<PORTC2) | (0<<PORTC1) | (0<<PORTC0);

// Port D initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRD=(0<<DDD7) | (0<<DDD6) | (0<<DDD5) | (0<<DDD4) | (0<<DDD3) | (0<<DDD2) | (0<<DDD1) | (0<<DDD0);
// State: Bit7=P Bit6=P Bit5=P Bit4=P Bit3=P Bit2=P Bit1=P Bit0=P 
PORTD=(1<<PORTD7) | (1<<PORTD6) | (1<<PORTD5) | (1<<PORTD4) | (1<<PORTD3) | (1<<PORTD2) | (1<<PORTD1) | (1<<PORTD0);

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: 7.813 kHz
// Mode: Normal top=0xFF
// OC0 output: Disconnected
// Timer Period: 32.768 ms
TCCR0=(0<<WGM00) | (0<<COM01) | (0<<COM00) | (0<<WGM01) | (1<<CS02) | (0<<CS01) | (1<<CS00);
TCNT0=0x00;
OCR0=0x00;

// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=(0<<OCIE2) | (0<<TOIE2) | (0<<TICIE1) | (0<<OCIE1A) | (0<<OCIE1B) | (0<<TOIE1) | (0<<OCIE0) | (1<<TOIE0);

// Alphanumeric LCD initialization
// Connections are specified in the
// Project|Configure|C Compiler|Libraries|Alphanumeric LCD menu:
// RS - PORTB Bit 1
// RD - PORTB Bit 2
// EN - PORTB Bit 3
// D4 - PORTB Bit 4
// D5 - PORTB Bit 5
// D6 - PORTB Bit 6
// D7 - PORTB Bit 7
// Characters/line: 16
lcd_init(16);

// Global enable interrupts
#asm("sei")

while (1)
      {
      switch(state){
        case clock:
        #asm("sei")
            if (i>30){
                i=0;
                sec++;
            }
            if (sec==60){
                sec=0;
                min++;
            }
            if (min==60){
                min=0;
                hour++;
            }
            if (hour==24)
                hour=0;      
      
            lcd_gotoxy(0,0);
            sprintf(str,"%02d : %02d : %02d",hour,min,sec);
            lcd_puts(str);
            
            if(KEY_SET == 0){
                delay_ms(200);
                state = set_hour;
                }
            break;
            
        case set_hour:
            #asm("cli")
            lcd_gotoxy(0,0);
            sprintf(str,"%02d : %02d : %02d",hour,min,sec);
            lcd_puts(str);
            lcd_gotoxy(0,1);
            lcd_puts("--              ");
            if(KEY_SET == 0){
                delay_ms(200);
                state = clock;
                lcd_clear();
                }
            if(KEY_RIGHT == 0){
                delay_ms(200);
                state = set_min;
            }
            if(KEY_UP == 0){
                delay_ms(200);
                hour++;
                hour = hour > 23 ? 0 : hour;
            } 
            break;              
            
        case set_min:
            #asm("cli")
            lcd_gotoxy(0,0);
            sprintf(str,"%02d : %02d : %02d",hour,min,sec);
            lcd_puts(str);
            lcd_gotoxy(0,1);
            lcd_puts("     --         ");
            if(KEY_SET == 0){
                delay_ms(200);
                state = clock;
                lcd_clear();
                }
            if(KEY_RIGHT == 0){
                delay_ms(200);
                state = set_sec;
            }
            if(KEY_UP == 0){
                delay_ms(200);
                min++;
                min = min > 59 ? 0 : min;
            } 
            break;

        case set_sec:
            #asm("cli")
            lcd_gotoxy(0,0);
            sprintf(str,"%02d : %02d : %02d",hour,min,sec);
            lcd_puts(str);
            lcd_gotoxy(0,1);
            lcd_puts("          --");
            if(KEY_SET == 0){
                delay_ms(200);
                state = clock;
                lcd_clear();                
                }
            if(KEY_RIGHT == 0){
                delay_ms(200);
                state = set_hour;
            }
            if(KEY_UP == 0){
                delay_ms(200);
                sec++;
                sec = sec > 59 ? 0 : sec;
            } 
            break;        
      }
}
}
