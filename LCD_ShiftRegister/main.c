#include "lcd.h"

#include <mega32.h>
#include <delay.h>

void send_0(void)
{
    CLK_0;
    DATA_0;
    CLK_1;
    CLK_0;
}

void send_1(void)
{
    CLK_0;
    DATA_1;
    CLK_1;
    CLK_0;
}

void send(unsigned char Data, unsigned char Cmd)
{   
    unsigned char i;
    for ( i = 0; i < 8; i++)
    {
        if(Data & 0x80)
            send_1();
        else
            send_0();
        Data = Data << 1;
    }
    for ( i = 0; i < 8; i++)
    {
        if(Cmd & 0x80)
            send_1();
        else
            send_0();
        Cmd = Cmd << 1;
    }
    EN_0;
    EN_1;
    delay_us(500);
    EN_0;
    
}


void LCD_CMD(unsigned char cmd){
    send(cmd, 0x00); //rs=0, en=0
    send(cmd, 0x80); //rs=0, en=1
    send(cmd, 0x00); //rs=0, en=0
}
void LCD_DATA(unsigned char data){
    send(data, 0x40); //rs=1, en=0
    send(data, 0xC0); //rs=1, en=1
    send(data, 0x40); //rs=1, en=0
}
void lcd_init(){
    LCD_CMD(0x38); //init 2x16 LCD
    LCD_CMD(0x0C); //display on, cursor off
    LCD_CMD(0x01); //clear
    LCD_CMD(0x80);//first column, first row 
 
}
void lcd_clear(void){
    LCD_CMD(0x01); //clear
}
void lcd_gotoxy(unsigned char x, unsigned char y){
    int i;
    if(x){
        LCD_CMD(0xC0);    //first column, second row
        for (i=0; i<y; i++)
        LCD_CMD(0x14);    //shift cursor right
        }
    else{
        for (i=0; i<y; i++)
        LCD_CMD(0x14);    //shift cursor right
        }
}
void lcd_putchar(unsigned char ch){
    LCD_DATA(ch);
    }
void lcd_puts(char *str){
    int i=0;
    while(str[i] != 0){
    lcd_putchar(str[i]);
    i++;
    }
}
