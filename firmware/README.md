# Firmware

Embedded C for the MSP430G2553, built in Code Composer Studio. The four folders are the bring-up stages in the order I worked through them. Each one is a complete program.

| Folder | What it proves |
|---|---|
| `01_led_pwm` | Clock and timers are running: heartbeat LED, plus an LED dimmed by PWM from the potentiometer |
| `02_lcd_adc` | I2C LCD output and the ADC: prints a title and the duty cycle as a percent |
| `03_ultrasonic` | Sensor timing: triggers the HC-SR04, reads the echo time, prints distance in mm and inches |
| `04_range_finder` | Everything together. This is what runs on the finished board |

## Distance math

The echo time comes back as a count of 10 microsecond timer ticks. Sound travels about 3.4 mm in 10 microseconds, and the pulse goes out and back, so each tick is 1.7 mm of range:

```
mm     = ticks * 3.4 / 2
inches = ticks * 0.066929        (1.7 mm / 25.4)
```

The inches value is printed with one decimal place without using floating-point `printf`, by computing the whole part and the tenths digit separately.

## Building

The programs include `Junior_Design.h`, a hardware driver header (clock, timer, ADC, I2C LCD, and echo-timing routines) that was supplied to me. It is not my work, so it is not in this repo. To build, put that header next to `main.c` and set its pin section to the values in `pin_config.h`.

`pin_config.h` holds my pin choices for this board.
