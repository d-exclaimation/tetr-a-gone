//
//  hexagone.c
//  
//  Main module for the game consisting of the state definitions and all game related functions
//
//  Authored by vno16 and ski102 on 30 Sep 2022
//

#include "hexagone.h"

/**
 * @brief Cast an untyped memory address as the game states
 * 
 * @warning Unsafe operation with the assumption the memory address points valid game states
 * 
 * @param data An untyped memory address
 * @returns A typed memory addres
 */
Hexagone_t* hexagone_from(void* data)
{
    return (Hexagone_t*) data;
}

/**
 * @brief Move the player on a specific directin
 * 
 * @param game The game states
 * @param dir The direction where the player is moving towards
 */
void hexagone_move(Hexagone_t* game, const Vector2_t dir)
{
    // Apply physics on the previous location
    hexagone_physics(game, game->player);

    // Move player
    game->player = vec2_clamp(vec2_add(game->player, dir));

    // Perform checks
    hexagone_audit(game);
}

/**
 * @brief Apply physics to the platform on a specific location
 * 
 * @param game The game states
 * @param loc The location in the map to apply physics to
 */
void hexagone_physics(Hexagone_t* game, const Vector2_t loc)
{   
    // Don't apply physics to an already broken platform
    if (hexagone_fallen_p(game, loc)) {
        return;
    }

    game->map[loc.y][loc.x]--;
}

/**
 * @brief Performs check on the player and the current state of the game if the game has ended or not 
 *
 * @param game The game states 
 */
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

/**
 * @brief Check if the current location is standing on top a broken platform
 * 
 * @param game The game states
 * @param loc The location in the map to be checked
 * 
 * @returns True if the location is on top a broken platform
 */
bool hexagone_fallen_p(const Hexagone_t* game, const Vector2_t loc)
{
    return game->map[loc.y][loc.x] == BROKEN;
}

/**
 * @brief Check if the game has ended or not
 * 
 * @param game The game states
 * 
 * @returns True if the player either had lost or won
 */
bool hexagone_ended_p(const Hexagone_t* game)
{
    // Win or Lose are over 10 enums
    return game->state >= WIN;
}