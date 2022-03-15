#ifndef _LCD_H
#define _LCD_H

#define PORTC PORT
#define data 1
#define clk 0
#define en 2
/*
#define data_0 PORTC &= ~(1<<data)
#define data_1 PORTC |= (1<<data)
#define clk_0 PORTC &= ~(1<<clk)
#define clk_1 PORTC |= (1<<clk)
#define en_0 PORTC &= ~(1<<en)
#define en_1 PORTC |= (1<<en)
*/
#pragma used+

void send(unsigned char);
void lcd_init(void);
void lcd_clear(void);
void lcd_gotoxy(int, int);
void lcd_putchar(char);
void lcd_puts(char *);

#pragma used-
#endif 
