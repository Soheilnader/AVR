#ifndef _LCD_H
#define _LCD_H

#define PORT PORTC
#define CLK 0
#define DATA 1
#define EN 2

#define CLK_0 PORT &= ~(1<<CLK)
#define CLK_1 PORT |= (1<<CLK)
#define DATA_0 PORT &= ~(1<<DATA)
#define DATA_1 PORT |= (1<<DATA)
#define EN_0 PORT &= ~(1<<EN)
#define EN_1 PORT |= (1<<EN)

#pragma used+

void lcd_init(void);
void lcd_clear(void);
void lcd_gotoxy(unsigned char, unsigned char);
void lcd_putchar(unsigned char);
void lcd_puts(char *);

#pragma used-
#endif 
