//
//  hexagone.h
//  
//  Main module for the game consisting of the state definitions and all game related functions
//
//  Authored by vno16 and ski102 on 30 Sep 2022
//

#ifndef HEXAGONE_H
#define HEXAGONE_H

#include "vector2.h"

/*!
 * \typedef Case_t
 * \brief All possible cases of the game
 */
typedef enum {
    GOING = 1,
    WIN = 10,
    LOSE = 20
} Case_t;


/*!
 * \typedef Platform_t
 * \brief The possible states of each platform
 */
typedef enum {
    BROKEN = 0,
    ALMOST,
    PARTIAL,
    RIGID
} Platform_t;

/**
 * \typedef Map_t
 * \brief A 2D array of all platforms on the map
 */
typedef Platform_t Map_t[MAX_Y + 1][MAX_X + 1];

/*!
 * \typedef Vector2_t
 * \brief All states of the game
 * 
 * \param player The current position of the player
 * \param map The current state of the map
 * \param state The current case of the game
 */
typedef struct {
    Vector2_t player;
    Map_t map;
    Case_t state;
} Hexagone_t;


/*!
 * \brief Move the player on a specific directin
 * 
 * \param game The game states
 * \param dir The direction where the player is moving towards
 */
void hexagone_move(Hexagone_t* game, const Vector2_t dir);

/*!
 * \brief Apply physics to the platform on a specific location
 * 
 * \param game The game states
 * \param loc The location in the map to apply physics to
 */
void hexagone_physics(Hexagone_t* game, const Vector2_t loc);

/**
 * \brief Performs check on the player and the current state of the game if the game has ended or not 
 *
 * \param game The game states 
 * \param callback Additional actions done if the gane has ended not before the checks (NULL for no further action)
 */
void hexagone_audit(Hexagone_t* game, void (*callback)(void));


/**
 * \brief Check if the current location is standing on top a broken platform
 * 
 * \param game The game states
 * \param loc The location in the map to be checked
 * 
 * \returns True if the location is on top a broken platform
 */
bool hexagone_fallen_p(const Hexagone_t* game, const Vector2_t loc);


/*!
 * \brief Check if the game has ended or not
 * 
 * \param game The game states
 * 
 * \returns True if the player either had lost or won
 */
bool hexagone_ended_p(const Hexagone_t* game);

#endif