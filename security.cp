#line 1 "D:/WALEED/live_person/Client_6/Security_system/security.c"
sbit LCD_RS at RC4_bit;
sbit LCD_EN at RC5_bit;
sbit LCD_D4 at RC0_bit;
sbit LCD_D5 at RC1_bit;
sbit LCD_D6 at RC2_bit;
sbit LCD_D7 at RC3_bit;

sbit LCD_RS_Direction at TRISC4_bit;
sbit LCD_EN_Direction at TRISC5_bit;
sbit LCD_D4_Direction at TRISC0_bit;
sbit LCD_D5_Direction at TRISC1_bit;
sbit LCD_D6_Direction at TRISC2_bit;
sbit LCD_D7_Direction at TRISC3_bit;





unsigned char time,t1,q1,w1,e1,i,a=1;
void system(void);
void RBINT_ISR(void);

void interrupt(void)
{
if(INTCON.RBIF==1)
 {
 RBINT_ISR();
 }
}

void RBINT_ISR()
{
i=PORTB;
INTCON.RBIF=0;
}

char txt1[] = "No Zone Armed";
char txt2[] = "Zone 1 Armd";
char txt3[] = "Zone 2 Armd";
char txt4[] = "Zone 3 Armd";
char txt5[] = "Zone 1&2 Armd";
char txt6[] = "Zone 1&3 Armd";
char txt7[] = "Zone 2&3 Armd";
char txt8[] = "Ready to Arm";
char txt9[] = "System Armed in";
char txt10[] = " Sec";
char txt11[] = "System Armed";
char txt12[] = "Breach";

void main()
{

 char b=0;
 time=10;
 ANSELH=0x00;
 TRISC = 0;
 TRISB = 0xFF;
 PORTB = 0xFF;
 IOCB=0xFF;
 OPTION_REG=0x80;
 INTCON=0xC8;
 Lcd_Init();
 Lcd_Cmd(_LCD_CURSOR_OFF);
 i=PORTB;
abc:
 time=10;
 b=1;

  PORTC.RC6 =0;
  PORTC.RC7 =0;
 while(1)
 {
 while(time>0)
 {

 t1=time/10;
 q1=time%10;
 w1=t1%10;
 e1=t1/10;
 q1=q1|0x30;
 w1=w1|0x30;
 e1=e1|0x30;

 if(i>8)
 --time;

 system();
 Delay_ms(999);

 Lcd_Cmd(_LCD_CLEAR);
 Lcd_Cmd(_LCD_CURSOR_OFF);
 }

 if(i==15 && a>0)
 {
 Lcd_Out(1,1,txt11);
  PORTC.RC6 =1;
 b=0;
 }
 while(b)
 {
 Lcd_Cmd(_LCD_CLEAR);
 Lcd_Cmd(_LCD_CURSOR_OFF);
 Lcd_Out(1,1,txt12);
 Delay_ms(1000);
  PORTC.RC7 =1;
 }

 if(i<15)
 {
 --a;
 goto abc;
 }

 }
}

void system()
{
switch(i)
 {
 case 1:
 Lcd_Out(1,1,txt2);
 time=10;
 a=1;
 break;

 case 2:
 Lcd_Out(1,1,txt3);
 time=10;
 a=1;
 break;

 case 3:
 Lcd_Out(1,1,txt5);
 time=10;
 a=1;
 break;

 case 4:
 Lcd_Out(1,1,txt4);
 time=10;
 a=1;
 break;

 case 5:
 Lcd_Out(1,1,txt6);
 time=10;
 a=1;
 break;

 case 6:
 Lcd_Out(1,1,txt7);
 time=10;
 a=1;
 break;

 case 7:
 Lcd_Out(1,1,txt8);
 time=10;
 a=1;
 break;

 case 9:
 Lcd_Out(1,1,txt2);
 Lcd_Chr(2, 4, w1);
 Lcd_Chr(2, 5, q1);
 Lcd_Out(2,6,txt10);
 break;

 case 10:
 Lcd_Out(1,1,txt3);
 Lcd_Chr(2, 4, w1);
 Lcd_Chr(2, 5, q1);
 Lcd_Out(2,6,txt10);
 break;

 case 11:
 Lcd_Out(1,1,txt5);
 Lcd_Chr(2, 4, w1);
 Lcd_Chr(2, 5, q1);
 Lcd_Out(2,6,txt10);
 break;

 case 12:
 Lcd_Out(1,1,txt4);
 Lcd_Chr(2, 4, w1);
 Lcd_Chr(2, 5, q1);
 Lcd_Out(2,6,txt10);
 break;

 case 13:
 Lcd_Out(1,1,txt6);
 Lcd_Chr(2, 4, w1);
 Lcd_Chr(2, 5, q1);
 Lcd_Out(2,6,txt10);
 break;

 case 14:
 Lcd_Out(1,1,txt7);
 Lcd_Chr(2, 4, w1);
 Lcd_Chr(2, 5, q1);
 Lcd_Out(2,6,txt10);
 break;

 case 15:
 Lcd_Out(1,1,txt9);
 Lcd_Chr(2, 4, w1);
 Lcd_Chr(2, 5, q1);
 Lcd_Out(2,6,txt10);
 break;

 default:
 Lcd_Out(1,1,txt1);
 a=1;
 break;
 }
}
