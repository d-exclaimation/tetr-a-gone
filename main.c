//
//  main.c
//  
//  Main entry point of the application
//
//  Authored by vno16 and ski102 on 30 Sep 2022
//

#include "system.h"
#include "pacer.h"
#include "hexagone.h"
#include "led.h"
#include "communication.h"
#include "io.h"

#define PACER_RATE 500
#define BLINK_RATE 10

/**
 * \brief A collective setup function
 */
static void setup(void)
{
    system_init();
    pacer_init(PACER_RATE);
    led_init();
    comms_init();
    io_init(PACER_RATE, BLINK_RATE);
}


int main(void)
{
    Hexagone_t game = {
        .player = vec2_inv(VEC2_ZERO),
        .other = vec2(-1, -1),
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

        pacer_wait();

        led_off();

        comms_subscribe(&game);

        display(&game);

        control(&game);

    }

    return 0;
}

