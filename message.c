//
//  msg.c
//  
//  Module for handling communication msg encoding and decoding
//
//  Authored by vno16 and ski102 on 04 Oct 2022
//

#include "message.h"

/**
 * @brief Create a encoded message using the typeno and the vector payload
 * 
 * @param typeno The type number for the message
 * @param vector The vector payload
 * 
 * @returns Encoded packet in 8 bit 
 */
Message_t message(const Typeno_t typeno, const Vector2_t vector)
{
    return (Message_t) {
        typeno, vector
    };
}

/**
 * @brief Create a message to signal the end of a game
 * 
 * @returns Ending message 
 */
Message_t message_end(void)
{
    // Game over does not need a payload, so zero on the payload
    return message(GAME_OVER, VEC2_ZERO);
}

/**
 * @brief Create a message to signal the inverted location of this player to the other board
 * 
 * @param player The location of this player
 * @returns The player location message from the given vector 
 */
Message_t message_player_vec2(const Vector2_t player)
{
    // Player position must be inverted before sending
    const Vector2_t inverted = vec2_inv(player);
    return message(PLAYER_POSITION, inverted);
}

/**
 * @brief Create a message to signal the inverted location of the platform to apply force to the other board
 * 
 * @param player The location of the platform to apply force to
 * @returns The platform force message from the given vector 
 */
Message_t message_force_vec2(const Vector2_t location)
{
    // Platform position must be inverted before sending
    const Vector2_t inverted = vec2_inv(location);
    return message(PLATFORM_FORCE, inverted);
}

/**
 * @brief Encode outgoing message into a 8 bit integer packet.
 * 
 * @internal 
 * p(t, x, y) = (t * 70) + (x * 7) + y
 * 
 * Outputs:
 *  - 70...210
 * @endinternal
 * 
 * @param msg Message to be encoded
 * 
 * 
 * @returns 8 bit unsigned integer for the message
 */
Packet_t message_encode(const Message_t msg)
{
    const Vector2_t vector = msg.payload;

    // Encoding uses different bases where the typeno is the highest digit followed by the column and row
    // This ensures the msg is at most 255 and at least 0 (For info look at message.h)
    return msg.typeno * TYPE_DISTANCE + vector.x * COL_DISTANCE + vector.y * ROW_DISTANCE; 
}


/**
 * @brief Decode incoming packet
 * 
 * @internal 
 * t(p) = p / 70
 * x(p) = p % 70 / 7
 * y(p) = p % 7
 * 
 * Inputs:
 *  - 70...210
 * @endinternal
 * 
 * @param packet 8 bit integer packet
 * 
 * @returns Possible decoded message from the packet, otherwise an invalid message is returned
 */
Message_t message_decode(const Packet_t packet)
{
    const uint8_t raw_typeno = packet / TYPE_DISTANCE;
    const uint8_t raw_payload = packet % TYPE_DISTANCE;

    // Double check packet is within the expected values (For info look at message.h)
    const bool not_higher = packet <= (GAME_OVER * TYPE_DISTANCE);
    const bool not_lower = packet >= TYPE_DISTANCE;
    const bool is_within_range = not_higher && not_lower && raw_payload <= (MAX_X * COL_DISTANCE + MAX_Y * ROW_DISTANCE);

    // If either the payload or typeno is not within the appropriate boundaries, packet is invalid
    if (!is_within_range) {
        return message(INVALID_PACKET, VEC2_ZERO);
    }

    const Vector2_t payload = vec2(raw_payload / COL_DISTANCE, raw_payload % COL_DISTANCE / ROW_DISTANCE);
    return message(raw_typeno, payload);
}