#include <mega32.h>
#include <delay.h>

//#define lcd_data_port PORTD 
#define rs PORTC.0 
#define en PORTC.1 

void LCD_CMD(unsigned char cmd){
    PORTD=cmd;
    rs = 0;
    en = 1;
    delay_ms(1);
    en = 0;
    delay_ms(1); 
}
void LCD_DATA(char data){
    PORTD=data;
    rs = 1;
    en = 1;
    delay_ms(1);
    en = 0;
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
 if(y==1){
 LCD_CMD(0xC0);
 delay_ms(1);
 for (i=0; i<x; i++)
 LCD_CMD(0x14);
 }
 if(y==0){
 for (i=0; i<x; i++)
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

void main()
{
DDRC=0xFF;
DDRD=0xFF;

PORTC=0;
PORTD=0;



lcd_init();
 



 lcd_putchar('A');
 delay_ms(1000);
 lcd_clear();
 lcd_gotoxy(0,1);
  lcd_putchar('A');
  delay_ms(1000);
  lcd_clear();
 lcd_gotoxy(5,1);

 lcd_puts("salam");
    while(1){
    
    }
}
