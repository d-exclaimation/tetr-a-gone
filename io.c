//
//  io.c
//  hex-a-gone
//
//  Created by vno16 on 16:05.
//

#include "io.h"

/*!
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


/*!
 * All the PIOs for LED Matrix columns
 */
static const pio_t cols[] = {
    LEDMAT_COL1_PIO,
    LEDMAT_COL2_PIO,
    LEDMAT_COL3_PIO,
    LEDMAT_COL4_PIO,
    LEDMAT_COL5_PIO
}; 

/*!
 * Previous column that has been turned on
 */
static int8_t prev_col = 0;

/*!
 * Current column that has not been turned on
 */
static int8_t curr_col = 0;

/*!
 * Display blinking rate
 */
static int8_t rate = 12;

/*!
 * Current blinking period (on if 0, otherwise off)
 */
static int8_t blinked = 0;

void io_init(pacer_rate_t pacer_rate, uint8_t blink_rate)
{
    ledmat_init();
    navswitch_init();
    rate = blink_rate;
    tinygl_init(pacer_rate);
    tinygl_font_set(&font5x5_1);
    tinygl_text_mode_set(TINYGL_TEXT_MODE_STEP);
    
}

/*! TODO: Update to use the current hexagone API */
void control(Hexagone_t* game)
{
    Vector2_t movement = VEC2_ZERO;
    navswitch_update();

    // TODO: Change to allow whenever the game has not ended
    if (game->state != GOING)
        return;
    
    if (navswitch_push_event_p(NAVSWITCH_NORTH)) {
        movement = VEC2_NORTH;
        
    }
    
    if (navswitch_push_event_p(NAVSWITCH_SOUTH)) {
        movement = VEC2_SOUTH;
    }

    if (navswitch_push_event_p(NAVSWITCH_EAST)) {
        movement = VEC2_EAST;
    }

    if (navswitch_push_event_p(NAVSWITCH_WEST)) {
        movement = VEC2_WEST;
    }

    if (!vec2_eq(movement, VEC2_ZERO)) {
        comms_publish(message_force_vec2(game->player));
        hexagone_move(game, movement);
        comms_publish(message_player_vec2(game->player));
    }

    // Close the communications as the game has ended
    if (hexagone_ended_p(game)) {
        comms_publish(message_end());
    }
}


void display(const Hexagone_t* game)
{
    if (hexagone_ended_p(game)) {
        tinygl_text(game->state == WIN ? "W" : "L");
        tinygl_update();
        return;
    }

    // Turn off any previusly turned on columns
    pio_output_high(cols[prev_col]);

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
    pio_output_low(cols[curr_col]);


    // Set previous column and wait for next iteration from the pacer
    prev_col = curr_col;

    curr_col++;

    // Start over
    if (curr_col > MAX_X) {
        curr_col = 0;
        blinked = (blinked + 1) % rate;
    }
}