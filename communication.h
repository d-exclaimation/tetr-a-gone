//
//  communication.h
//  
//  Module for handling IR communications
//
//  Authored by vno16 and ski102 on 07 Oct 2022
//

#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include "hexagone.h"
#include "message.h"
#include "ir_uart.h"

/*!
 * \brief Initialize communications
 */
void comms_init(void);

/*!
 * \brief Publish a message through infrared
 * 
 * \param msg The message being sent
 */
void comms_publish(const Message_t msg);


/*!
 * \brief Subscribe to any incoming messages and apply changes to the game
 * 
 * \param game The game states
 */
void comms_subscribe(Hexagone_t* game);

#endif