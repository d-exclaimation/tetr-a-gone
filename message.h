//
//  message.h
//  
//  Module for handling communication message encoding and decoding (using base 7)
//
//  Authored by vno16 and ski102 on 04 Oct 2022
//

#ifndef MESSAGE_H
#define MESSAGE_H

#include "vector2.h"

#define TYPE_DISTANCE 49
#define COL_DISTANCE 7
#define ROW_DISTANCE 1

typedef enum {
    PLAYER_POSITION = 1,
    PLATFORM_FORCE = 2,
    GAME_OVER = 3,
    INVALID_PACKET = 0
} MType_t; 

typedef struct {
    MType_t typeno;
    Vector2_t payload;
} Message_t;

/**
 * \typedef Packet_t
 * \brief The IR packet
 */
typedef uint8_t Packet_t;

/**
 * \brief Create a encoded message using the typeno and the vector payload
 * 
 * \param typeno The type number for the message
 * \param vector The vector payload
 * 
 * \returns Encoded packet in 8 bit 
 */
Message_t message(const MType_t typeno, const Vector2_t vector);


/**
 * \brief Create a message to signal the end of a game
 * 
 * \returns Ending message 
 */
Message_t message_end(void);

/**
 * \brief Create a message to signal the inverted location of this player to the other board
 * 
 * \param player The location of this player
 * \returns The player location message from the given vector 
 */
Message_t message_player_vec2(const Vector2_t player);

/**
 * \brief Create a message to signal the inverted location of the platform to apply force to the other board
 * 
 * \param player The location of the platform to apply force to
 * \returns The platform force message from the given vector 
 */
Message_t message_force_vec2(const Vector2_t location);


/**
 * \brief Encode outgoing message into a 8 bit integer packet
 * 
 * \param msg Message to be encoded
 * 
 * \returns 8 bit unsigned integer for the message
 */
Packet_t message_encode(const Message_t msg);

/**
 * \brief Decode incoming packet
 * 
 * \param packet 8 bit integer packet
 * 
 * \returns Possible decoded message from the packet, otherwise an invalid message is returned
 */
Message_t message_decode(const Packet_t packet);

#endif