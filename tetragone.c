//
//  tetragone.c
//  
//  Main module for the game consisting of the state definitions and all game related functions
//
//  Authored by Vincent ~ (vno16) and Natalie Kim (ski102) on 30 Sep 2022
//

#include "tetragone.h"

/**
 * @brief Cast an untyped memory address as the game states
 * 
 * @warning Unsafe operation with the assumption the memory address points valid game states
 * 
 * @param data An untyped memory address
 * @returns A typed memory addres
 */
Tetragone_t* tetragone_from(void* data)
{
    return (Tetragone_t*) data;
}

/**
 * @brief Move the player on a specific directin
 * 
 * @param game The game states
 * @param dir The direction where the player is moving towards
 */
void tetragone_move(Tetragone_t* game, const Vector2_t dir)
{
    // Apply physics on the previous location
    tetragone_physics(game, game->player);

    // Move player
    game->player = vec2_clamp(vec2_add(game->player, dir));

    // Perform checks
    tetragone_audit(game);
}

/**
 * @brief Apply physics to the platform on a specific location
 * 
 * @param game The game states
 * @param loc The location in the map to apply physics to
 */
void tetragone_physics(Tetragone_t* game, const Vector2_t loc)
{   
    // Don't apply physics to an already broken platform
    if (tetragone_fallen_p(game, loc)) {
        return;
    }

    game->map[loc.y][loc.x]--;
}

/**
 * @brief Performs check on the player and the current state of the game if the game has ended or not 
 *
 * @param game The game states 
 */
void tetragone_audit(Tetragone_t* game)
{
    // If game had already ended prior, no action is performed
    if (tetragone_ended_p(game)) {
        return;
    }

    // If the player has not fallen yet, no action is performed
    if (!tetragone_fallen_p(game, game->player) && !tetragone_trapped_p(game, game->player)) {
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
bool tetragone_fallen_p(const Tetragone_t* game, const Vector2_t loc)
{
    return game->map[loc.y][loc.x] == BROKEN;
}

/**
 * @brief Check if the current location is standing on top a broken platform
 * 
 * @param game The game states
 * @param loc The location in the map to be checked
 * 
 * @returns True if the location is on top a broken platform
 */
bool tetragone_trapped_p(const Tetragone_t* game, const Vector2_t loc)
{   
    const Vector2_t all_dirs[] = {VEC2_NORTH, VEC2_SOUTH, VEC2_EAST, VEC2_WEST};
    for (size_t i = 0; i < (sizeof(all_dirs) / sizeof(all_dirs[0])); i++) {
        const Vector2_t side = vec2_add(loc, all_dirs[i]);
        if (!tetragone_fallen_p(game, side)) {
            return false;
        }
    }
    return true;
}

/**
 * @brief Check if the game has ended or not
 * 
 * @param game The game states
 * 
 * @returns True if the player either had lost or won
 */
bool tetragone_ended_p(const Tetragone_t* game)
{
    // Win or Lose are over 10 enums
    return game->state >= WIN;
}