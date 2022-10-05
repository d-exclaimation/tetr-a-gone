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

/**
 * \brief The distance multiplied for the type when encoded
 */
#define TYPE_DISTANCE 49

/**
 * \brief The distance multiplied for the vector payload column when encoded
 */
#define COL_DISTANCE 7

/**
 * \brief The distance multiplied for the vector payload row when encoded
 */
#define ROW_DISTANCE 1

/**
 * \typedef Typeno_t
 * \brief Possible type number and what they represents
 */
typedef enum {
    PLAYER_POSITION = 1,
    PLATFORM_FORCE = 2,
    GAME_OVER = 3,
    INVALID_PACKET = 0
} Typeno_t; 

/**
 * \typedef Message_t
 * \brief A human readable intermediate data for the packet before encoding
 * 
 * \param typeno A number for the type of message
 * \param payload A vector payload for the message
 */
typedef struct {
    Typeno_t typeno;
    Vector2_t payload;
} Message_t;

/**
 * \typedef Packet_t
 * \brief The encoded IR packet
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
Message_t message(const Typeno_t typeno, const Vector2_t vector);


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
 * \internal
 * Encoding using base 7 with 3 fields:
 * - 2: Type number (valid range 0 - 3)
 * - 1: Vector payload column (valid range 0 - 4)
 * - 0: Vector payload row (valid range 0 - 6)
 * - Valid values: 0 - 146, 200 - 246, and 300
 * \endinternal
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
 * \internal
 * Encoding using base 7 with 3 fields:
 * - 2: Type number (valid range 0 - 3)
 * - 1: Vector payload column (valid range 0 - 4)
 * - 0: Vector payload row (valid range 0 - 6)
 * - Valid values: 0 - 146, 200 - 246, and 300
 * \endinternal
 * 
 * \returns Possible decoded message from the packet, otherwise an invalid message is returned
 */
Message_t message_decode(const Packet_t packet);

#endif