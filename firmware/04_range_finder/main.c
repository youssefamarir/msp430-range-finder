// Stage 4: the integrated range finder program that runs on the final board

#include <msp430.h>
#include <stdio.h>
#include "Junior_Design.h"

static unsigned int ADC_Result;
static unsigned long int d1;
int d_1, d_10;

void main(void)
{
    //Just my static LCD and the display buffers
    char Data[] = "Junior Design"; //Title shown each cycle
    char Data2[32] = "";           //Distance display buffer
    char Data3[32] = "";           //Duty-cycle display buffer

    //Hardware / peripheral initialization
    Init_HW();          //Initialize MSP430, clocks, ADC, timers, etc.
    LCD_Initialize();   //Initialize LCD interface

    //Status LEDs configuration
    P1DIR |= BIT3;      //Set P1.3 as output status my heartbeat LED
    P1OUT |= BIT3;      //Turn on P1.3 MCU alive indicator
    P2DIR |= BIT0;      //Set P2.0 as output blink LED
    P2OUT |= BIT0;      //Start P2.0 high

    //Just my main application loop
    while (1)
    {
        LCD_CLRscreen();           //Clear LCD each cycle
        LCD_String(Data);          //Prints out Junior Design on first line

        //Reads my potentiometer
        ADC_Result = ADC_Read();   //Sample analog input
        Duty = (int)((float)ADC_Result / (float)10.23); //Map 0-1023 -> 0-100%
        sprintf(Data3, " %d%%", (int)Duty);             //Format duty for LCD

        //Ultrasonic trigger & capture
        Ultrasonic_Trigger();          //Send trigger pulse
        Delay_Timer(DELAYT_100ms);     //Short wait before reading echo
        d1 = Ultrasonic_Echo_Read();   //Raw echo timing count

        //Split distance inches into
        d_1 = (int)((float)d1 * 0.066929);
        d_10 = (int)((float)d1 * 0.66929) - d_1 * 10;

        //Format: distance in mm inches
        sprintf(Data2, "%dmm %d.%din",
            (int)((float)d1 * 3.4 / 2.0), //Convert to mm from echo time
            d_1,
            d_10);

        //Second line LCD output
        LCD_Cursor_Postion(0x40);  //Move to 2nd line
        LCD_String(Data2);         //Show distance
        LCD_String(Data3);         //Show duty cycle

        //Blinks my led to show active loop
        P2OUT ^= BIT0;             //Toggle P2.0 each update

        Delay_Timer(DELAYT_500ms); //500 ms refresh rate
    }
}
