//
//  main.c
//  group_207
//
//  Created by vno16 on 19:56.
//

#include "system.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"
#include "point.h"
#include "io.h"
#include "led.h"
#include "ir_uart.h"

#define PACER_RATE 500
#define BLINK_RATE 10
#define MESSAGE_RATE 10


bool should_shrink(void)
{
    if (!ir_uart_read_ready_p()) {
        return false;
    }
    int8_t res = ir_uart_getc();
    return res == 'N';
}

int main(void)
{
    system_init(); 
    ir_uart_init();
    led_init();
    io_init(PACER_RATE, BLINK_RATE);
    tinygl_init (PACER_RATE);
    tinygl_font_set (&font5x7_1);
    tinygl_text_speed_set(MESSAGE_RATE);
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);

    Point_t player = point(0, 0);  

    bool hasEnded = false;

    while (1) {
        if (max_rows() < 0 && !hasEnded) {
            tinygl_text("GAME OVER!!!");
            hasEnded = true;
        }

        if (hasEnded) {
            pacer_wait();
            tinygl_update();
            led_on();
            continue;
        }

        led_off();
        display(&player);
        control(&player);

        if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
            ir_uart_putc('N');
        }


        // If received signal, shrink the column
        if (should_shrink()) {
            shrink_rows(&player);
            led_on();
        }
    }

    return 0;
}