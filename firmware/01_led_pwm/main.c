// Stage 1: heartbeat LED and potentiometer-controlled PWM LED

#include <msp430.h>
#include <stdio.h>
#include "Junior_Design.h"

static unsigned int ADC_Result;

void main(void)
{
    Init_HW();          //Initialize MSP430 hardware and timers
    LCD_Initialize();   //Initialize LCD not used a lot in this step

    P1DIR |= BIT3;      //Configures my P1.3 as output the status LED
    P2DIR |= BIT0;      //Configures my P2.0 as output the PWM LED

    while(1)
    {
        ADC_Result = ADC_Read();                        //Reads my potentiometer
        Duty = (int)((float)ADC_Result / (float)10.23); //Scale to 0-100% duty
        // PWM hardware just automatically adjusts LED brightness based on the Duty value
        Delay_Timer(DELAYT_500ms);                      //500ms refresh delay
    }
}
