// Stage 2: strings and integers on the I2C LCD, potentiometer read through the ADC

#include <msp430.h>
#include <stdio.h>
#include "Junior_Design.h"

static unsigned int ADC_Result;

void main(void)
{
    char Data[] = "Junior Design"; //just the title
    char Data3[32] = "";           //Duty cycle string buffer

    Init_HW();
    LCD_Initialize();

    while(1)
    {
        LCD_CLRscreen();           //Clears the LCD for each refresh
        LCD_String(Data);          //Prints title on first line

        ADC_Result = ADC_Read();   //Reads my potentiometer voltage
        Duty = (int)((float)ADC_Result / (float)10.23); //Just convertd to percent
        sprintf(Data3, " %d%%", (int)Duty);             //Formats as percent text

        LCD_Cursor_Postion(0x40);  //Moves to second line
        LCD_String(Data3);         //Shows my duty cycle

        Delay_Timer(DELAYT_500ms); //Updates pretty much every half second
    }
}
