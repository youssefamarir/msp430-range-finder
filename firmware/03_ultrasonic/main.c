// Stage 3: trigger the ultrasonic sensor, time the echo, show distance in mm and inches

#include <msp430.h>
#include <stdio.h>
#include "Junior_Design.h"

static unsigned long int d1;
int d_1, d_10;

void main(void)
{
    char Data2[32] = "";  //Just the distance buffer

    Init_HW();            //Initialize GPIO, timers, ultrasonic
    LCD_Initialize();     //Setup my LCD interface

    while(1)
    {
        LCD_CLRscreen();            //Refreshes display

        Ultrasonic_Trigger();       //Just sends trigger pulse
        Delay_Timer(DELAYT_100ms);  //Waits for 100 ms for echo return
        d1 = Ultrasonic_Echo_Read();

        //Converts my raw echo time to mm and inches
        d_1 = (int)((float)d1 * 0.066929);
        d_10 = (int)((float)d1 * 0.66929) - d_1 * 10;
        sprintf(Data2, "%dmm %d.%din", (int)((float)d1 * 3.4 / 2.0), d_1, d_10);

        LCD_Cursor_Postion(0x40);   //Moves to second LCD line
        LCD_String(Data2);          //Prints out my distance value I calced

        Delay_Timer(DELAYT_500ms);  //Updates every half a second
    }
}
