#include "lcd.h"

#include <mega32.h>
#include <delay.h>

void send_0(void)
{
    CLK_0;
    DATA_0;
    CLK_1;
    delay_ms(1);
    CLK_0;
}

void send_1(void)
{
    CLK_0;
    DATA_1;
    CLK_1;
    delay_ms(1);
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
    delay_ms(1);
    EN_0;
    
}


void LCD_CMD(unsigned char cmd){
    send(cmd, 0x80);
    //rs = 0;
    //en = 1;
    delay_ms(1);
    send(cmd, 0x00);
    //rs = 0;
    //en = 1;
    //en = 0;
    delay_ms(1); 
}
void LCD_DATA(char data){
    send(data, 0xC0);
    //rs = 1;
    //en = 1;
    delay_ms(1);
    send(data, 0x40);
    //en = 0;
    delay_ms(1);
}
void lcd_init(){
 LCD_CMD(0x38); //init
  LCD_CMD(0x0C); //display on

 LCD_CMD(0x01); //clear
  LCD_CMD(0x80);//first colimn, first row 
 
}
void lcd_clear(void){
 LCD_CMD(0x01); //clear

}
void lcd_gotoxy(int x, int y){
int i;
 if(x){
 LCD_CMD(0xC0);
 delay_ms(1);
 for (i=0; i<y; i++)
 LCD_CMD(0x14);
 }
else{
 for (i=0; i<y; i++)
 LCD_CMD(0x14);
 }
}
void lcd_putchar(char ch){
LCD_DATA(ch);
}
void lcd_puts(char *str){
int i=0;
delay_ms(1);
 while(str[i] != 0)
 {
  lcd_putchar(str[i]);
  i++;
 }
}
