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
#include "hexagone.h"

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

    // 0 + 0 = 0
    vec = vec2_add(VEC2_ZERO, VEC2_ZERO);
    if (!vec2_eq(vec, VEC2_ZERO))
        return FAIL;

    // 0 + 1 = 1
    vec = vec2_add(VEC2_ZERO, vec2(1, 1));
    if (!vec2_eq(vec, vec2(1, 1)))
        return FAIL;


    // 1, 0 + 0, 1 = 1, 1
    vec = vec2_add(VEC2_EAST, VEC2_SOUTH);
    if (!vec2_eq(vec, vec2(1, 1)))
        return FAIL;

    // -1, 0 + 0, -1 = -1, -1
    vec = vec2_add(VEC2_WEST, VEC2_NORTH);
    if (!vec2_eq(vec, vec2(-1, -1)))
        return FAIL;

    return OK;
}

static Testcode_t vector2_inv_test(void)
{
    Vector2_t vec;

    // ~(0, 0) = 4, 6
    vec = vec2_inv(VEC2_ZERO);
    if (!vec2_eq(vec, vec2(MAX_X, MAX_Y)))
        return FAIL;

    // ~(4, 6) = 0, 0
    vec = vec2_inv(vec2(MAX_X, MAX_Y));
    if (!vec2_eq(vec, VEC2_ZERO))
        return FAIL;

    // ~(2, 2) = (2, 4)
    vec = vec2_inv(vec2(2, 2));
    if (!vec2_eq(vec, vec2(MAX_X - 2, MAX_Y - 2)))
        return FAIL;

    return OK;
}


static Testcode_t vector2_clamp_test(void)
{
    Vector2_t vec;

    // | 1, 1 | = 1, 1
    vec = vec2_clamp(vec2(1, 1));
    if (!vec2_eq(vec, vec2(1, 1)))
        return FAIL;
    
    // | -1, -1 | = 0, 0
    vec = vec2_clamp(vec2(-1, -1));
    if (!vec2_eq(vec, VEC2_ZERO))
        return FAIL;

    // | 1, 1 | using (0 - 0, 0 - 0) = 0, 0
    vec = vec2_clamp_in(vec2(1, 1), 0, 0, 0, 0);
    if (!vec2_eq(vec, VEC2_ZERO))
        return FAIL;

    return OK;
}

// -- Message

static Testcode_t message_types_test(void)
{
    Message_t msg;

    // Message end should have 3 typeno and no payload
    msg = message_end();
    if (msg.typeno != GAME_OVER || !vec2_eq(msg.payload, VEC2_ZERO))
        return FAIL;

    // Message player should have 1 typeno and the inverted payload
    msg = message_player_vec2(VEC2_ZERO);
    if (msg.typeno != PLAYER_POSITION || !vec2_eq(msg.payload, vec2(MAX_X, MAX_Y)))
        return FAIL;

    // Message player should have 2 typeno and the inverted payload
    msg = message_force_vec2(VEC2_ZERO);
    if (msg.typeno != PLATFORM_FORCE || !vec2_eq(msg.payload, vec2(MAX_X, MAX_Y)))
        return FAIL;

    return OK;
}

static Testcode_t message_encode_test(void)
{
    Packet_t packet;

    packet = message_encode(message_end());

    // Message encode should not go beyond 147
    if (packet > 147)
        return FAIL;

    // Message encode should not alter any typeno
    if (packet / 49 != GAME_OVER)
        return FAIL;

    // Message encode should not alter any payload
    if (packet % 49 != 0)
        return FAIL;

    packet = message_encode(message_force_vec2(VEC2_ZERO));

    if (packet > 147)
        return FAIL;
    
    // Message encode should not alter any typeno
    if (packet / 49 != GAME_OVER)
    if (packet / 49 != PLATFORM_FORCE)
        return FAIL;

    // Message encode should not alter any payload's x
    if (packet % 49 / 7 != MAX_X)
        return FAIL;
    
    // Message encode should not alter any payload's y
    if (packet % 7 / 1 != MAX_Y)
        return FAIL;

    return OK;
}

static Testcode_t message_decode_test(void)
{
    Message_t msg;

    // Message end (3 * 49)
    msg = message_decode(147);

    // Decode you not alter message and is able to parse correctly
    if (msg.typeno != GAME_OVER || !vec2_eq(msg.payload, VEC2_ZERO))
        return FAIL;

    // Decode you do the inverse of encode and cancel each other out
    msg = message_decode(message_encode(message_end())); 
    if (msg.typeno != GAME_OVER || !vec2_eq(msg.payload, VEC2_ZERO))
        return FAIL;

    // Decode should not lose or alter any field
    msg = message_decode(message_encode(message(1, vec2(1, 1))));
    if (msg.typeno != 1 || !vec2_eq(msg.payload, vec2(1, 1)))
        return FAIL;

    return OK;
}


// -- Hexagone

static Testcode_t hexagone_moving_test(void)
{
    Hexagone_t game = {
        .map = {{0}},
        .other = VEC2_ZERO,
        .player = VEC2_ZERO,
        .state = GOING
    };

    // Stand still should slowly break the platform undyrneath and keep the player position
    game.map[0][0] = RIGID;
    game.player = VEC2_ZERO;
    hexagone_move(&game, VEC2_ZERO);
    if (game.map[0][0] != PARTIAL || !vec2_eq(game.player, VEC2_ZERO) || game.state != GOING)
        return FAIL;

    // Moving in any direction should slowly break previous position and successfully move the player
    game.map[0][0] = RIGID;
    game.map[1][0] = RIGID;
    game.player = VEC2_ZERO;
    hexagone_move(&game, VEC2_SOUTH);
    if (game.map[0][0] != PARTIAL || !vec2_eq(game.player, vec2(0, 1)) || game.state != GOING)
        return FAIL;

    // Moving to an invalid positon should have the same effect as standing still
    game.map[0][0] = RIGID;
    game.player = VEC2_ZERO;
    hexagone_move(&game, VEC2_NORTH);
    if (game.map[0][0] != PARTIAL || !vec2_eq(game.player, VEC2_ZERO) || game.state != GOING)
        return FAIL;

    // Moving to a broken platform will set the game state to LOSE
    game.map[0][0] = RIGID;
    game.map[1][0] = BROKEN;
    game.player = VEC2_ZERO;
    hexagone_move(&game, VEC2_SOUTH);
    if (!vec2_eq(game.player, vec2(0, 1)) || game.state != LOSE)
        return FAIL;

    return OK;
}


static Testcode_t hexagone_physics_test(void)
{
    Hexagone_t game = {
        .map = {{0}},
        .other = VEC2_ZERO,
        .player = VEC2_ZERO,
        .state = GOING
    };  

    // Platform should slowly break
    game.map[0][0] = RIGID;
    hexagone_physics(&game, VEC2_ZERO);
    if (game.map[0][0] != PARTIAL)
        return FAIL;

    hexagone_physics(&game, VEC2_ZERO);
    if (game.map[0][0] != ALMOST)
        return FAIL;
    
    hexagone_physics(&game, VEC2_ZERO);
    if (game.map[0][0] != BROKEN)
        return FAIL;

    // Should not go beyond BROKEN = 0
    hexagone_physics(&game, VEC2_ZERO);
    if (game.map[0][0] != BROKEN)
        return FAIL;

    return OK;
}


static Testcode_t hexagone_audit_test(void)
{
    Hexagone_t game = {
        .map = {{0}},
        .other = VEC2_ZERO,
        .player = VEC2_ZERO,
        .state = GOING
    };  

    // Audit should change game state properly
    game.map[0][0] = BROKEN;
    game.player = VEC2_ZERO;
    hexagone_audit(&game, NULL);
    if (game.state != LOSE)
        return FAIL;

    game.state = GOING;
    game.map[0][0] = RIGID;
    game.player = VEC2_ZERO;
    hexagone_audit(&game, NULL);
    if (game.state != GOING)
        return FAIL;

    return OK;   
}

static Testcode_t hexagone_predicate_test(void)
{
    Hexagone_t game = {
        .map = {{0}},
        .other = VEC2_ZERO,
        .player = VEC2_ZERO,
        .state = GOING
    };  

    game.map[0][0] = RIGID;
    if (hexagone_fallen_p(&game, VEC2_ZERO))
        return FAIL;

    game.map[0][0] = PARTIAL;
    if (hexagone_fallen_p(&game, VEC2_ZERO))
        return FAIL;

    game.map[0][0] = ALMOST;
    if (hexagone_fallen_p(&game, VEC2_ZERO))
        return FAIL;

    game.map[0][0] = BROKEN;
    if (!hexagone_fallen_p(&game, VEC2_ZERO))
        return FAIL;

    game.state = GOING;
    if (hexagone_ended_p(&game))
        return FAIL;

    game.state = LOSE;
    if (!hexagone_ended_p(&game))
        return FAIL;

    game.state = WIN;
    if (!hexagone_ended_p(&game))
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
        unit("Hexagone Moving test", &hexagone_moving_test),
        unit("Hexagone Physics test", &hexagone_physics_test),
        unit("Hexagone Audit test", &hexagone_audit_test),
        unit("Hexagone Predicate test", &hexagone_predicate_test),
    };
    test_all(units, sizeof(units) / sizeof(Unit_t));
    return 0;
}

