//
//  io.h
//  hex-a-gone
//
//  Created by vno16 on 16:05.
//

/** TODO: Split display and controls into their own module */

#ifndef IO_H
#define IO_H

#include "hexagone.h"
#include "system.h"
#include "pio.h"
#include "ledmat.h"
#include "navswitch.h"
#include "communication.h"
#include "tinygl.h"
#include "pacer.h"
#include "../fonts/font5x5_1.h"

/**
 * @brief Initialize navswitch and LED matrix
 * 
 * @param blink_rate The amount of delay between each blink (1/rate)
 * @param pacer_rate The pacer rate
 */
void io_init(pacer_rate_t pacer_rate,  uint8_t blink_rate);

/**
 * @brief Retreive control input and apply to the game
 * 
 * @param game The game itself
 */
void control(Hexagone_t* game);

/**
 * @brief Display the current state of the game 
 * 
 * @param game The game itself
 */
void display(const Hexagone_t* game);

#endif