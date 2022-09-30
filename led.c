//
//  led.c
//  
//  Module for controlling the blue led because the existing driver one is confusing :)
//
//  Authored by vno16 and ski102 on 30 Sep 2022
//

#include "led.h"

static bool is_active = false;

void led_init(void)
{
    is_active = false;
    pio_config_set(LED1_PIO, PIO_OUTPUT_LOW);
}

void led_on(void)
{
    is_active = true;
    pio_output_high(LED1_PIO);
}

void led_off(void)
{
    is_active = false;
    pio_output_low(LED1_PIO);
}

void led_toggle(void)
{
    if (is_active) {
        led_off();
    } else {
        led_on();
    }
}

bool led_active_p(void)
{
    return is_active;
}