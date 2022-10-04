//
//  main.c
//  
//  Main entry point of the application
//
//  Authored by vno16 and ski102 on 30 Sep 2022
//

/** TODO: Add the imports for all the necessary modules from the API */
/** TODO: Add the imports for all game modules */
#include "hexagone.h"

/**
 * \brief A collective setup function
 */
static void setup(void)
{
    /** TODO: Initialise everything here */
}

int main(void)
{
    Hexagone_t game = {
        .player = VEC2_ZERO,
        .other = vec2_inv(VEC2_ZERO),
        .state = GOING,
        /** TODO: I don't know how to fill in a 2D array with the same values :( */
        .map = {
            {RIGID, RIGID, RIGID, RIGID, RIGID},
            {RIGID, RIGID, RIGID, RIGID, RIGID},
            {RIGID, RIGID, RIGID, RIGID, RIGID},
            {RIGID, RIGID, RIGID, RIGID, RIGID},
            {RIGID, RIGID, RIGID, RIGID, RIGID},
            {RIGID, RIGID, RIGID, RIGID, RIGID},
            {RIGID, RIGID, RIGID, RIGID, RIGID}
        }
    };

    setup();

    while (1) {
        /** TODO: Wait using pacer here */

        /** TODO: Display update for game state or end screen here */

        /** TODO: Get inputs and control the game here */

        /** TODO: Handle communications here */

        /** TODO: Perform housekeeping for edge cases here */
    }

    return 0;
}

