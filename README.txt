This project demonstrates programming interrupts and configuring/using the timers on the MSP432P401R.
 
This is done through the implimentation of a blinking LED. The Red LED will blink (on/off) every second, 
and the second LED (RGB) to will change to next color every 0.5 seconds. 
The two LEDs are out of phase by precisely 0.1 seconds.To accomplish this, TimerA0 is used UP mode 
(and corresponding interrupts) to trigger the RED LED and TimerA1 in UP/DOWN mode (and corresponding interrupts) 
to trigger the RGB LED.