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
// LCD module connections

#define ARMED PORTC.RC6
#define BREACH PORTC.RC7

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

void RBINT_ISR()                 // Interrupt service routine for PORTB interrupt on change
{
i=PORTB;                         // For every interrupt save the value of PORTB in variable "i"
INTCON.RBIF=0;                   // Must clear PORTB interrupt on change flag
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
  ANSELH=0x00;                          // Enable PORTB for Digital input
  TRISC = 0;                            // PORTC as output
  TRISB = 0xFF;                         // PORTB as input
  PORTB = 0xFF;                         // Initial value of PORTB on Reset
  IOCB=0xFF;                            // Enable the bits of PORTB for interrupt
  OPTION_REG=0x80;
  INTCON=0xC8;                          // PORTB Interrupt on change enabled
  Lcd_Init();                           // Initialize LCD, Built in function
  Lcd_Cmd(_LCD_CURSOR_OFF);             // Cursor off
  i=PORTB;                              // Save PORTB value in variable
abc:
  time=10;
  b=1;

  ARMED=0;
  BREACH=0;
  while(1)
  {
  while(time>0)
  {

  t1=time/10;         //////////////////////////////////////////////////////
  q1=time%10;         //////////////////////////////////////////////////////
  w1=t1%10;
  e1=t1/10;           ////// Conversion of decimal value of ///////////////
  q1=q1|0x30;         ////// count down timer to Ascii to /////////////////
  w1=w1|0x30;         ////// display it on LCD ////////////////////////////
  e1=e1|0x30;         //////////////////////////////////////////////////////

  if(i>8)
  --time;             // Decrease the timer value if i>8

  system();           // Function to display the status of security on LCD according to input
  Delay_ms(999);      // To produce a delay of 1 sec

  Lcd_Cmd(_LCD_CLEAR);                // Clear display
  Lcd_Cmd(_LCD_CURSOR_OFF);           // Cursor off
  }

  if(i==15 && a>0)                    // Condition to check that system is armed or not
  {
  Lcd_Out(1,1,txt11);                 // Write "System Armed" on LCD
  ARMED=1;                            // LED to indicate that system is armed
  b=0;                                // Controls the security breach loop
  }
  while(b)                            // start of security breach loop
  {
  Lcd_Cmd(_LCD_CLEAR);                // Clear display
  Lcd_Cmd(_LCD_CURSOR_OFF);           // Cursor off
  Lcd_Out(1,1,txt12);                 // Write "Breach" on LCD
  Delay_ms(1000);
  BREACH=1;                           // LED to indicate that system is breached
  }

  if(i<15)                            // Condition to check that system is breached after successful system arming or not
  {
  --a;
  goto abc;                           // Jump back to the start of code to check the security breach after successful system arming
  }

  }
}

void system()
{
switch(i)                             // Compare the value of i and display message accordigly
  {
  case 1:
  Lcd_Out(1,1,txt2);                 // Write "Zone 1 Armed" on LCD
  time=10;                           // Reset the value of timer
  a=1;
  break;

  case 2:
  Lcd_Out(1,1,txt3);                 // Write "Zone 2 Armed" on LCD
  time=10;                           // Reset the value of timer
  a=1;
  break;

  case 3:
  Lcd_Out(1,1,txt5);                 // Write "Zone 1&2 Armed" on LCD
  time=10;                           // Reset the value of timer
  a=1;
  break;

  case 4:
  Lcd_Out(1,1,txt4);                 // Write "Zone 3 Armed" on LCD
  time=10;                           // Reset the value of timer
  a=1;
  break;

  case 5:
  Lcd_Out(1,1,txt6);                 // Write "Zone 1&3 Armed" on LCD
  time=10;                           // Reset the value of timer
  a=1;
  break;

  case 6:
  Lcd_Out(1,1,txt7);                 // Write "Zone 2&3 Armed" on LCD
  time=10;                           // Reset the value of timer
  a=1;
  break;

  case 7:
  Lcd_Out(1,1,txt8);                 // Write "Ready to Arm" on LCD
  time=10;                           // Reset the value of timer
  a=1;
  break;

  case 9:
  Lcd_Out(1,1,txt2);                 // Write "Zone 1 Armed" on LCD, when the button to arm system is pressed
  Lcd_Chr(2, 4, w1);                 // Write the MSB ASCii value of timer on LCD
  Lcd_Chr(2, 5, q1);                 // Write the LSB ASCii value of timer on LCD
  Lcd_Out(2,6,txt10);                // Write "Sec" on LCD
  break;

  case 10:
  Lcd_Out(1,1,txt3);                 // Write "Zone 2 Armed" on LCD, when the button to arm system is pressed
  Lcd_Chr(2, 4, w1);                 // Write the MSB ASCii value of timer on LCD
  Lcd_Chr(2, 5, q1);                 // Write the LSB ASCii value of timer on LCD
  Lcd_Out(2,6,txt10);                // Write "Sec" on LCD
  break;

  case 11:
  Lcd_Out(1,1,txt5);                 // Write "Zone 1&2 Armed" on LCD, when the button to arm system is pressed
  Lcd_Chr(2, 4, w1);                 // Write the MSB ASCii value of timer on LCD
  Lcd_Chr(2, 5, q1);                 // Write the LSB ASCii value of timer on LCD
  Lcd_Out(2,6,txt10);                // Write "Sec" on LCD
  break;

  case 12:
  Lcd_Out(1,1,txt4);                 // Write "Zone 3 Armed" on LCD, when the button to arm system is pressed
  Lcd_Chr(2, 4, w1);                 // Write the MSB ASCii value of timer on LCD
  Lcd_Chr(2, 5, q1);                 // Write the LSB ASCii value of timer on LCD
  Lcd_Out(2,6,txt10);                // Write "Sec" on LCD
  break;

  case 13:
  Lcd_Out(1,1,txt6);                 // Write "Zone 1&3 Armed" on LCD, when the button to arm system is pressed
  Lcd_Chr(2, 4, w1);                 // Write the MSB ASCii value of timer on LCD
  Lcd_Chr(2, 5, q1);                 // Write the LSB ASCii value of timer on LCD
  Lcd_Out(2,6,txt10);                // Write "Sec" on LCD
  break;

  case 14:
  Lcd_Out(1,1,txt7);                 // Write "Zone 2&3 Armed" on LCD, when the button to arm system is pressed
  Lcd_Chr(2, 4, w1);                 // Write the MSB ASCii value of timer on LCD
  Lcd_Chr(2, 5, q1);                 // Write the LSB ASCii value of timer on LCD
  Lcd_Out(2,6,txt10);                // Write "Sec" on LCD
  break;

  case 15:
  Lcd_Out(1,1,txt9);                 // Write "System Armed in" on LCD
  Lcd_Chr(2, 4, w1);                 // Write the MSB ASCii value of timer on LCD
  Lcd_Chr(2, 5, q1);                 // Write the LSB ASCii value of timer on LCD
  Lcd_Out(2,6,txt10);                // Write "Sec" on LCD
  break;

  default:
  Lcd_Out(1,1,txt1);                 // Write "No Zone is Armed"
  a=1;
  break;
  }
}
