//
//  communication.h
//  
//  Module for handling IR communications
//
//  Authored by Vincent ~ (vno16) and Natalie Kim (ski102) on 07 Oct 2022
//

#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include "tetragone.h"
#include "message.h"
#include "ir_uart.h"
#include "led.h"

/**
 * @brief The amount of repetitions done for redundancy
 */
#define REDUNDANCY_LIMIT 5

/**
 * @brief Initialize communications
 */
void comms_init(void);

/**
 * @brief Publish a message through infrared
 * 
 * @param msg The message being sent
 */
void comms_publish(const Message_t msg);

/**
 * @brief Redundantly publish a message through infrared to combat any losses
 * 
 * @param msg The message being sent
 */
void comms_redundant_publish(const Message_t msg);

/**
 * @brief Subscribe to any incoming messages and apply changes to the game
 * 
 * @param game The game states
 */
void comms_subscribe(Tetragone_t* game);

#endif