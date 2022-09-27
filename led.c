//
//  led.c
//  hex-a-gone
//
//  Created by vno16 on 15:31.
//

#include "led.h"

void led_init(void)
{
    pio_config_set(LED1_PIO, PIO_OUTPUT_LOW);    
}

void led_on(void)
{
    pio_output_high(LED1_PIO);
}

void led_off(void)
{
    pio_output_low(LED1_PIO);
}
