//
//  io.h
//  hex-a-gone
//
//  Created by vno16 on 16:05.
//

#ifndef IO_H
#define IO_H

#include "point.h"
// #include "system.h"
// #include "pio.h"
// #include "pacer.h"
// #include "ledmat.h"
// #include "navswitch.h"

/**
 * \brief Initialize navswitch and LED matrix
 * 
 * \param pacer_rate The rate of the pacer
 * \param blink_rate The amount of delay between each blink (1/rate)
 */
// void io_init(pacer_rate_t pacer_rate, uint8_t blink_rate);

/**
 * \brief Retreive control input and apply to the game
 * 
 * \param player The game itself
 */
void control(Point_t* player);

/**
 * \brief Display the current state of the game 
 * 
 * \param game The game itself
 */
void display(const Point_t* player);

#endif