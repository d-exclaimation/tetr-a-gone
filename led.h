//
//  led.h
//  hex-a-gone
//
//  Created by vno16 on 15:27.
//

#ifndef LED_H
#define LED_H

#include "system.h"
#include "pio.h"

/**
 * \brief Initialize Blue LED
 */
void led_init(void);

/**
 * \brief Turn on LED
 */
void led_on(void);

/**
 * \brief Turn off LED
 */
void led_off(void);

#endif