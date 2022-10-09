//
//  led.h
//  
//  Module for controlling the blue led because the existing driver one is confusing :)
//
//  Authored by Vincent ~ (vno16) and Natalie Kim (ski102) on 30 Sep 2022
//

#ifndef LED_H
#define LED_H

#include <stdbool.h>
#include "pio.h"
#include "system.h"

/**
 * @brief Initialise the Blue LED PIO as output start as turned off
 */
void led_init(void);

/**
 * @brief Turn on Blue LED
 */
void led_on(void);

/**
 * @brief Turn off Blue LED
 */
void led_off(void);

/**
 * @brief Toggle LED from on to off or off to on
 */
void led_toggle(void);

/**
 * @brief Get the status of the LED
 * 
 * @returns True if the LED is currently on
 */
bool led_active_p(void);

#endif