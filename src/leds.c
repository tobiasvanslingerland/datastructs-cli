// Control of LEDs on launchpad

// RTOS header files
#include <ti/drivers/GPIO.h>

// Driver configuration
#include "ti_drivers_config.h"

// Project header files
#include "leds.h"

void leds_init(void){
    // Configure the LED pins
    GPIO_setConfig(CONFIG_GPIO_LED_0, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW); // Red
    GPIO_setConfig(CONFIG_GPIO_LED_1, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW); // Yellow
    GPIO_setConfig(CONFIG_GPIO_LED_2, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW); // Green
}

void leds_zero(void)
{
    leds_offRed();
    leds_offYellow();
    leds_offGreen();
}
void leds_one(void)
{
    leds_onRed();
    leds_offYellow();
    leds_offGreen();
}
void leds_two(void)
{
    leds_offRed();
    leds_onYellow();
    leds_offGreen();
}
void leds_three(void)
{
    leds_onRed();
    leds_onYellow();
    leds_offGreen();
}
void leds_four(void)
{
    leds_offRed();
    leds_offYellow();
    leds_onGreen();
}
void leds_five(void)
{
    leds_onRed();
    leds_offYellow();
    leds_onGreen();
}
void leds_six(void)
{
    leds_offRed();
    leds_onYellow();
    leds_onGreen();
}
void leds_seven(void)
{
    leds_onRed();
    leds_onYellow();
    leds_onGreen();
}

void leds_toggleRed(void){
GPIO_toggle(CONFIG_GPIO_LED_0);
}
void leds_toggleYellow(void){
GPIO_toggle(CONFIG_GPIO_LED_1);
}
void leds_toggleGreen(void){
GPIO_toggle(CONFIG_GPIO_LED_2);
}

void leds_onRed(void){
    GPIO_write(CONFIG_GPIO_LED_0, CONFIG_GPIO_LED_ON);
}
void leds_onYellow(void){
    GPIO_write(CONFIG_GPIO_LED_1, CONFIG_GPIO_LED_ON);
}
void leds_onGreen(void){
    GPIO_write(CONFIG_GPIO_LED_2, CONFIG_GPIO_LED_ON);
}

void leds_offRed(void){
    GPIO_write(CONFIG_GPIO_LED_0, CONFIG_GPIO_LED_OFF);
}
void leds_offYellow(void){
    GPIO_write(CONFIG_GPIO_LED_1, CONFIG_GPIO_LED_OFF);
}
void leds_offGreen(void){
    GPIO_write(CONFIG_GPIO_LED_2, CONFIG_GPIO_LED_OFF);
}
