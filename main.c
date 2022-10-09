//
//  main.c
//  
//  Main entry point of the application
//
//  Authored by vno16 and ski102 on 30 Sep 2022
//

#include "system.h"
#include "hexagone.h"
#include "led.h"
#include "communication.h"
#include "io.h"
#include "task.h"


#define BLINK_PERIOD 10

#define SUBSCRIBE_TASK_RATE 750
#define DISPLAY_TASK_RATE 500
#define CONTROL_TASK_RATE 300
#define LED_TASK_RATE 20

/**
 * @brief A collective setup function
 */
static void setup(void)
{
    system_init();
    led_init();
    comms_init();
    io_init(DISPLAY_TASK_RATE, BLINK_PERIOD);
}

/**
 * @brief Task for polling / retreiving messages and applying changes to the game states accordingly
 * 
 * @param data The game states memory address
 */
static void subscribe_task(void* data)
{
    comms_subscribe(hexagone_from(data));
}

/**
 * @brief Task for outputing the game states into the LED matrix display
 * 
 * @param data The game states memory address
 */
static void display_task(void* data)
{
    io_display(hexagone_from(data));
}

/**
 * @brief Task for polling the navswitch inputs and applying changes to the game states accordingly
 * 
 * @param data The game states memory address
 */
static void control_task(void* data)
{
    io_control(hexagone_from(data));
}

/**
 * @brief Task for turning off the blue LED so it flickers at a clear and visible rate 
 * 
 * @param data The game states memory address
 */
static void led_task(__unused__ void* data)
{
    led_off();
}

int main(void)
{
    Hexagone_t game = {
        .player = vec2_inv(VEC2_ZERO),
        .other = VEC2_ZERO,
        .state = GOING,
        .map = {
            {RIGID, RIGID, RIGID, RIGID, RIGID, RIGID, RIGID, RIGID, RIGID, RIGID},
            {RIGID, RIGID, RIGID, RIGID, RIGID, RIGID, RIGID, RIGID, RIGID, RIGID},
            {RIGID, RIGID, RIGID, RIGID, RIGID, RIGID, RIGID, RIGID, RIGID, RIGID},
            {RIGID, RIGID, RIGID, RIGID, RIGID, RIGID, RIGID, RIGID, RIGID, RIGID},
            {RIGID, RIGID, RIGID, RIGID, RIGID, RIGID, RIGID, RIGID, RIGID, RIGID},
            {RIGID, RIGID, RIGID, RIGID, RIGID, RIGID, RIGID, RIGID, RIGID, RIGID},
            {RIGID, RIGID, RIGID, RIGID, RIGID, RIGID, RIGID, RIGID, RIGID, RIGID},
        }
    };

    task_t tasks[] = {
        {.func = subscribe_task, .period = TASK_RATE / SUBSCRIBE_TASK_RATE, .data = &game},
        {.func = display_task, .period = TASK_RATE / DISPLAY_TASK_RATE, .data = &game},
        {.func = control_task, .period = TASK_RATE / CONTROL_TASK_RATE, .data = &game},
        {.func = led_task, .period = TASK_RATE / LED_TASK_RATE},
    };

    setup();

    task_schedule(tasks, ARRAY_SIZE(tasks));

    return 0;
}

