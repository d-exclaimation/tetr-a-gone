//
//  test.c
//  
//  Unit test program
//
//  Authored by vno16 and ski102 on 07 Oct 2022
//

#include "unittest.h"
#include "vector2.h"
#include "message.h"

// -- Vector2

static Testcode_t vector2_eq_test(void)
{
    if (!vec2_eq(VEC2_EAST, VEC2_EAST))
        return FATAL;

    if (!vec2_eq(VEC2_ZERO, VEC2_ZERO))
        return FATAL;

    if (vec2_eq(VEC2_EAST, VEC2_WEST))
        return FATAL;

    if (vec2_eq(VEC2_NORTH, VEC2_SOUTH))
        return FATAL;

    if (vec2_eq(vec2(4, 7), vec2(7, 4)))
        return FATAL;

    return OK;
}

static Testcode_t vector2_add_test(void)
{
    Vector2_t vec;

    vec = vec2_add(VEC2_ZERO, VEC2_ZERO);
    if (!vec2_eq(vec, VEC2_ZERO))
        return FAIL;

    vec = vec2_add(VEC2_ZERO, vec2(1, 1));
    if (!vec2_eq(vec, vec2(1, 1)))
        return FAIL;

    vec = vec2_add(VEC2_ZERO, vec2(1, 1));
    if (!vec2_eq(vec, vec2(1, 1)))
        return FAIL;

    vec = vec2_add(VEC2_EAST, VEC2_SOUTH);
    if (!vec2_eq(vec, vec2(1, 1)))
        return FAIL;

    vec = vec2_add(VEC2_WEST, VEC2_NORTH);
    if (!vec2_eq(vec, vec2(-1, -1)))
        return FAIL;

    return OK;
}

static Testcode_t vector2_inv_test(void)
{
    Vector2_t vec;

    vec = vec2_inv(VEC2_ZERO);
    if (!vec2_eq(vec, vec2(MAX_X, MAX_Y)))
        return FAIL;

    vec = vec2_inv(vec2(MAX_X, MAX_Y));
    if (!vec2_eq(vec, VEC2_ZERO))
        return FAIL;

    vec = vec2_inv(vec2(2, 2));
    if (!vec2_eq(vec, vec2(MAX_X - 2, MAX_Y - 2)))
        return FAIL;

    return OK;
}


static Testcode_t vector2_clamp_test(void)
{
    Vector2_t vec;

    vec = vec2_clamp(vec2(1, 1));
    if (!vec2_eq(vec, vec2(1, 1)))
        return FAIL;
    
    vec = vec2_clamp(vec2(-1, -1));
    if (!vec2_eq(vec, VEC2_ZERO))
        return FAIL;

    vec = vec2_clamp_in(vec2(1, 1), 0, 0, 0, 0);
    if (!vec2_eq(vec, VEC2_ZERO))
        return FAIL;

    return OK;
}

// -- Message

static Testcode_t message_types_test(void)
{
    Message_t msg;

    msg = message_end();
    if (msg.typeno != GAME_OVER || !vec2_eq(msg.payload, VEC2_ZERO))
        return FAIL;

    msg = message_player_vec2(VEC2_ZERO);
    if (msg.typeno != PLAYER_POSITION || !vec2_eq(msg.payload, vec2(MAX_X, MAX_Y)))
        return FAIL;

    msg = message_force_vec2(VEC2_ZERO);
    if (msg.typeno != PLATFORM_FORCE || !vec2_eq(msg.payload, vec2(MAX_X, MAX_Y)))
        return FAIL;

    return OK;
}

static Testcode_t message_encode_test(void)
{
    Packet_t packet;

    packet = message_encode(message_end());

    if (packet > 147)
        return FAIL;

    if (packet / 49 != GAME_OVER)
        return FAIL;

    if (packet % 49 != 0)
        return FAIL;

    packet = message_encode(message_force_vec2(VEC2_ZERO));

    if (packet > 147)
        return FAIL;
    
    if (packet / 49 != PLATFORM_FORCE)
        return FAIL;

    if (packet % 49 / 7 != MAX_X)
        return FAIL;
    
    if (packet % 7 / 1 != MAX_Y)
        return FAIL;

    return OK;
}

static Testcode_t message_decode_test(void)
{
    Message_t msg;

    msg = message_decode(147);

    if (msg.typeno != GAME_OVER || !vec2_eq(msg.payload, VEC2_ZERO))
        return FAIL;

    msg = message_decode(message_encode(message_end())); 
    if (msg.typeno != GAME_OVER || !vec2_eq(msg.payload, VEC2_ZERO))
        return FAIL;

    msg = message_decode(message_encode(message(1, vec2(1, 1))));
    if (msg.typeno != 1 || !vec2_eq(msg.payload, vec2(1, 1)))
        return FAIL;

    return OK;
}

int main(void)
{
    Unit_t units[] = {
        unit("Vector 2 Equal test", &vector2_eq_test),
        unit("Vector 2 Add test", &vector2_add_test),
        unit("Vector 2 Invert test", &vector2_inv_test),
        unit("Vector 2 Clamp test", &vector2_clamp_test),
        unit("Message Types test", &message_types_test),
        unit("Message Encoding test", &message_encode_test),
        unit("Message Decoding test", &message_decode_test),
    };
    test_all(units, sizeof(units) / sizeof(Unit_t));
    return 0;
}

