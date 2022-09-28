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
 * Previous column that has been turned on
 */
static int8_t prev_col = 0;

/**
 * Current column that has not been turned on
 */
static int8_t curr_col = 0;

/**
 * Display blinking rate
 */
static int8_t rate = 12;

/**
 * Current blinking period (on if 0, otherwise off)
 */
static int8_t blinked = 0;

void io_init(pacer_rate_t pacer_rate, uint8_t blink_rate)
{
    pacer_init(pacer_rate);
    ledmat_init();
    navswitch_init();
    rate = blink_rate;
}


void control(Point_t* player)
{
    navswitch_update();

    if (max_rows() < 0)
        return;

    if (navswitch_push_event_p(NAVSWITCH_NORTH)) {
        *player = apply(*player, UP);
    }
    
    if (navswitch_push_event_p(NAVSWITCH_SOUTH)) {
        *player = apply(*player, DOWN);
    }

    if (navswitch_push_event_p(NAVSWITCH_EAST)) {
        *player = apply(*player, RIGHT);
    }

    if (navswitch_push_event_p(NAVSWITCH_WEST)) {
        *player = apply(*player, LEFT);
    }

}

void display(const Point_t* player, const Point_t* obj)
{
    // Turn off any previusly turned on columns
    pio_output_high(cols[prev_col]);

    for (int8_t row = 0; row <= MAX_ROW; row++) {

        if (max_rows() < row) {
            pio_output_low(rows[row]);
        } else if (player->col == curr_col && player->row == row) {
            pio_output_low(rows[row]);
        } else if (obj->col == curr_col && obj->row == row && !blinked) {
            pio_output_low(rows[row]);
        } else {
            pio_output_high(rows[row]);
        }
        
    }

    // Turn on current column
    pio_output_low(cols[curr_col]);


    // Set previous column and wait for next iteration from the pacer
    prev_col = curr_col;
    pacer_wait();
    curr_col++;
    
    if (curr_col > MAX_COL) {
        curr_col = 0;
        blinked = (blinked + 1) % rate;
    }
}