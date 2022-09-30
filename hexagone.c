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
    const Vector2_t new_pos = vec2_clamp(vec2_add(game->player, dir));
    
    // Apply physics on the previous location
    hexagone_physics(game, game->player);

    if (hexagone_fallen_p(game, new_pos)) {
        game->state = LOSE;
    }

    game->player = new_pos;
}

void hexagone_physics(Hexagone_t* game, const Vector2_t loc)
{   
    // Don't apply physics to an already broken platform
    if (hexagone_fallen_p(game, loc)) {
        return;
    }

    game->map[loc.y][loc.x] -= 1;
}

bool hexagone_fallen_p(const Hexagone_t* game, const Vector2_t loc)
{
    return game->map[loc.y][loc.x] == BROKEN;
}