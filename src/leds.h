// Control of LEDs on launchpad
#ifndef _Tobias_LEDS_
#define _Tobias_LEDS_

// Initialize leds
void leds_init(void);

// Set leds to decimal value
void leds_zero(void);
void leds_one(void);
void leds_two(void);
void leds_three(void);
void leds_four(void);
void leds_five(void);
void leds_six(void);
void leds_seven(void);

// Toggle led
void leds_toggleRed(void);
void leds_toggleYellow(void);
void leds_toggleGreen(void);

// Turn led on
void leds_onRed(void);
void leds_onYellow(void);
void leds_onGreen(void);

// Turn led off
void leds_offRed(void);
void leds_offYellow(void);
void leds_offGreen(void);

#endif
