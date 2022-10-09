//
//  io.c
//  hex-a-gone
//
//  Created by vno16 on 16:05.
//

#include "io.h"

/**
 * All the PIOs for LED Matrix rows
 */
static const pio_t rows[] = {
    LEDMAT_ROW1_PIO, 
    LEDMAT_ROW2_PIO, 
    LEDMAT_ROW3_PIO, 
    LEDMAT_ROW4_PIO, 
    LEDMAT_ROW5_PIO, 
    LEDMAT_ROW6_PIO,
    LEDMAT_ROW7_PIO
};


/**
 * All the PIOs for LED Matrix columns
 */
static const pio_t cols[] = {
    LEDMAT_COL1_PIO,
    LEDMAT_COL2_PIO,
    LEDMAT_COL3_PIO,
    LEDMAT_COL4_PIO,
    LEDMAT_COL5_PIO
}; 

/**
 * All the movement of the navswitch
 */
static const uint8_t options[] = {NAVSWITCH_NORTH, NAVSWITCH_SOUTH, NAVSWITCH_EAST, NAVSWITCH_WEST};

/**
 * All directions count
 */
static const size_t num_directions = 4;

/**
 * Previous column that has been turned on
 */
static int8_t prev_col = START_X;

/**
 * Current column that has not been turned on
 */
static int8_t curr_col = START_X;

/**
 * Display blinking rate
 */
static int8_t rate = 0;

/**
 * Current blinking period (on if 0, otherwise off)
 */
static int8_t blinked = 0;

void io_init(uint16_t display_rate, uint8_t blink_period)
{
    rate = blink_period;

    ledmat_init();
    navswitch_init();
    tinygl_init(display_rate);
    tinygl_font_set(&font5x5_1);
    tinygl_text_mode_set(TINYGL_TEXT_MODE_STEP);
}


/**
 * @brief Move player, while publishing both location of the player and the platform to apply physics to
 * 
 * @param game The game states to be modified
 * @param dir The direction the player is moving
 */
static void control_movement(Hexagone_t* game, const Vector2_t dir)
{
    comms_publish(message_force_vec2(game->player));
    hexagone_move(game, dir);
    comms_publish(message_player_vec2(game->player));
}

void control(Hexagone_t* game)
{
    // If the game has ended, no controls should be read
    if (hexagone_ended_p(game)) {
        return;
    }

    // Check all directions the navswitch might be pushed. 
    const Vector2_t directions[] = {VEC2_NORTH, VEC2_SOUTH, VEC2_EAST, VEC2_WEST};

    navswitch_update();
    for (size_t move = 0; move < num_directions; move++) {
        if (navswitch_push_event_p(options[move])) {
            control_movement(game, directions[move]);
            break;
        }
    }

    // Close the communications as the game has ended
    if (hexagone_ended_p(game)) {
        comms_publish(message_end());
    }
}


/**
 * @brief Show ending screen (W or L)
 *
 * @param game The game states to be displayed
 */
static void display_end_screen(const Hexagone_t* game)
{
    tinygl_text(game->state == WIN ? "W" : "L");
    tinygl_update();
}

/**
 * @brief Show the current column of the ongoing game 
 *
 * @param game The game states to be displayed
 */
static void display_game_screen(const Hexagone_t* game)
{
    // Turn off any previusly turned on columns
    pio_output_high(cols[prev_col - START_X]);

    for (int8_t row = 0; row <= MAX_Y; row++) {

        // Player 1 location during non-blink period
        if (game->player.x == curr_col && game->player.y == row && !blinked) {
            pio_output_low(rows[row]);
        
        // Player 2 location
        } else if (game->other.x == curr_col && game->other.y == row && !blinked) {
            pio_output_low(rows[row]);
        
        // Any hole location
        } else if (game->map[row][curr_col] == BROKEN) {
            pio_output_low(rows[row]);
        
        // Any non hole location
        } else {
            pio_output_high(rows[row]);
        }

    }

    // Turn on current column
    pio_output_low(cols[curr_col - START_X]);
}

void display(const Hexagone_t* game)
{
    // Show end screen if the game has ended instead of the game states
    if (hexagone_ended_p(game)) {
        display_end_screen(game);
    } else {
        display_game_screen(game);
    }

    // Set previous column and wait for next iteration from the pacer
    prev_col = curr_col;
    curr_col++;

    // Start over
    if (curr_col > MAX_X) {
        curr_col = START_X;
        blinked = (blinked + 1) % rate;
    }
}