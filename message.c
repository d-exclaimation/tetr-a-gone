//
//  msg.c
//  
//  Module for handling communication msg encoding and decoding (using base 7)
//
//  Authored by vno16 and ski102 on 04 Oct 2022
//

#include "message.h"

Message_t message(const Typeno_t typeno, const Vector2_t vector)
{
    return (Message_t) {
        typeno, vector
    };
}

Message_t message_end(void)
{
    // Game over does not need a payload, so zero on the payload
    return message(GAME_OVER, VEC2_ZERO);
}

Message_t message_player_vec2(const Vector2_t player)
{
    // Player position must be inverted before sending
    const Vector2_t inverted = vec2_inv(player);
    return message(PLAYER_POSITION, inverted);
}

Message_t message_force_vec2(const Vector2_t location)
{
    // Platform position must be inverted before sending
    const Vector2_t inverted = vec2_inv(location);
    return message(PLATFORM_FORCE, inverted);
}

Packet_t message_encode(const Message_t msg)
{
    const Vector2_t vector = msg.payload;

    // Encoding uses base 7 where the typeno is the highest number followed by the column and row
    // This ensures the msg is at most 255 and at least 0 (For info look at message.h)
    return msg.typeno * TYPE_DISTANCE + vector.x * COL_DISTANCE + vector.y * ROW_DISTANCE; 
}


Message_t message_decode(const Packet_t packet)
{
    const uint8_t raw_typeno = packet / TYPE_DISTANCE;
    const uint8_t raw_payload = packet % TYPE_DISTANCE;

    // Double check packet is within the expected values (For info look at message.h)
    const bool is_within_range = packet <= (GAME_OVER * TYPE_DISTANCE) && raw_payload <= (MAX_X * COL_DISTANCE + MAX_Y * ROW_DISTANCE);

    // If either the payload or typeno is not within the appropriate boundaries, packet is invalid
    if (!is_within_range) {
        return message(INVALID_PACKET, VEC2_ZERO);
    }

    const Vector2_t payload = vec2(raw_payload / COL_DISTANCE, raw_payload % COL_DISTANCE / ROW_DISTANCE);
    return message(raw_typeno, payload);
}