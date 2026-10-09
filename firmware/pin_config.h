// Pin assignments for the range finder board (MSP430G2553, 20-pin TSSOP).
// These are the values that go in the pin section of the driver header.

#define LCD_SCL          BIT6    // P1.6, pin 14 - I2C clock to the LCD backpack
#define LCD_SDA          BIT7    // P1.7, pin 15 - I2C data to the LCD backpack
#define USENSOR_TRIGGER  BIT5    // P2.5, pin 13 - ultrasonic trigger
#define ECHO_INTERUPT    BIT4    // P2.4, pin 12 - ultrasonic echo (through a 510/1k divider)
#define ADC_INPUTPIN     BIT0    // P1.0, pin 2  - potentiometer wiper
#define ADC_INPUT        INCH_0  // ADC10 channel for P1.0
#define ADC_LED          BIT3    // P1.3, pin 5  - PWM-dimmed LED
