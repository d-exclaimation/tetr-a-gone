//
//  hexagone.c
//  
//  Main module for the game consisting of the state definitions and all game related functions
//
//  Authored by vno16 and ski102 on 30 Sep 2022
//

#include "hexagone.h"

void hexagone_move(Hexagone_t* game, const Vector2_t dir)
{
    // Apply physics on the previous location
    hexagone_physics(game, game->player);

    // Move player
    game->player = vec2_clamp(vec2_add(game->player, dir));

    // Perform checks
    hexagone_audit(game);
}

void hexagone_physics(Hexagone_t* game, const Vector2_t loc)
{   
    // Don't apply physics to an already broken platform
    if (hexagone_fallen_p(game, loc)) {
        return;
    }

    game->map[loc.y][loc.x]--;
}

void hexagone_audit(Hexagone_t* game)
{
    // If game had already ended prior, no action is performed
    if (hexagone_ended_p(game)) {
        return;
    }

    // If the player has not fallen yet, no action is performed
    if (!hexagone_fallen_p(game, game->player)) {
        return;
    }

    game->state = LOSE;
}

bool hexagone_fallen_p(const Hexagone_t* game, const Vector2_t loc)
{
    return game->map[loc.y][loc.x] == BROKEN;
}

bool hexagone_ended_p(const Hexagone_t* game)
{
    // Win or Lose are over 10 enums
    return game->state >= WIN;
}