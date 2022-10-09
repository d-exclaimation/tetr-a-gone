//
//  led.c
//  
//  Module for controlling the blue led because the existing driver one is confusing :)
//
//  Authored by vno16 and ski102 on 30 Sep 2022
//

#include "led.h"

/**
 * A variable to keep track whether the blue LED is active or not
 */
static bool is_active = false;

/**
 * @brief Initialise the Blue LED PIO as output start as turned off
 */
void led_init(void)
{
    is_active = false;
    pio_config_set(LED1_PIO, PIO_OUTPUT_LOW);
}

/**
 * @brief Turn on Blue LED
 */
void led_on(void)
{
    is_active = true;
    pio_output_high(LED1_PIO);
}

/**
 * @brief Turn off Blue LED
 */
void led_off(void)
{
    is_active = false;
    pio_output_low(LED1_PIO);
}

/**
 * @brief Toggle LED from on to off or off to on
 */
void led_toggle(void)
{
    if (is_active) {
        led_off();
    } else {
        led_on();
    }
}

/**
 * @brief Get the status of the LED
 * 
 * @returns True if the LED is currently on
 */
bool led_active_p(void)
{
    return is_active;
}