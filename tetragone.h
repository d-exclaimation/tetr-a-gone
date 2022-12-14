//
//  tetragone.h
//  
//  Main module for the game consisting of the state definitions and all game related functions
//
//  Authored by Vincent ~ (vno16) and Natalie Kim (ski102) on 30 Sep 2022
//

#ifndef TETRAGONE_H
#define TETRAGONE_H

#include "vector2.h"

/**
 * @typedef Case_t
 * @brief All possible cases of the game
 */
typedef enum {
    GOING = 1,
    WIN = 10,
    LOSE = 20
} Case_t;


/**
 * @typedef Platform_t
 * @brief The possible states of each platform
 */
typedef enum {
    BROKEN = 0,
    ALMOST,
    PARTIAL,
    RIGID
} Platform_t;

/**
 * @typedef Map_t
 * @brief A 2D array of all platforms on the map
 */
typedef Platform_t Map_t[MAX_Y + 1][MAX_X + 1];

/**
 * @typedef Vector2_t
 * @brief All states of the game
 * 
 * @param player The current position of the player
 * @param player The current position of the other player
 * @param map The current state of the map
 * @param state The current case of the game
 */
typedef struct {
    Vector2_t player;
    Vector2_t other;
    Map_t map;
    Case_t state;
} Tetragone_t;


/**
 * @brief Cast an untyped memory address as the game states
 * 
 * @warning Unsafe operation with the assumption the memory address points valid game states
 * 
 * @param data An untyped memory address
 * @returns A typed memory addres
 */
Tetragone_t* tetragone_from(void* data);

/**
 * @brief Move the player on a specific directin
 * 
 * @param game The game states
 * @param dir The direction where the player is moving towards
 */
void tetragone_move(Tetragone_t* game, const Vector2_t dir);

/**
 * @brief Apply physics to the platform on a specific location
 * 
 * @param game The game states
 * @param loc The location in the map to apply physics to
 */
void tetragone_physics(Tetragone_t* game, const Vector2_t loc);

/**
 * @brief Performs check on the player and the current state of the game if the game has ended or not 
 *
 * @param game The game states 
 */
void tetragone_audit(Tetragone_t* game);


/**
 * @brief Check if the current location is standing on top a broken platform
 * 
 * @param game The game states
 * @param loc The location in the map to be checked
 * 
 * @returns True if the location is on top a broken platform
 */
bool tetragone_fallen_p(const Tetragone_t* game, const Vector2_t loc);

/**
 * @brief Check if the current location is surrounded by holes
 * 
 * @param game The game states
 * @param loc The location in the map to be checked
 * 
 * @returns True if the location is surrounded by holes from all possible directions
 */
bool tetragone_trapped_p(const Tetragone_t* game, const Vector2_t loc);

/**
 * @brief Check if the game has ended or not
 * 
 * @param game The game states
 * 
 * @returns True if the player either had lost or won
 */
bool tetragone_ended_p(const Tetragone_t* game);

#endif