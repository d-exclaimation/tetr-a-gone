//
//  main.c
//  group_207
//
//  Created by vno16 on 19:56.
//

#include <stdlib.h>
#include "system.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"
#include "point.h"
#include "io.h"
#include "led.h"
#include "ir_uart.h"

#define PACER_RATE 500
#define BLINK_RATE 8
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
    Point_t obj = point(MAX_ROW, MAX_COL);

    bool hasEnded = false;

    while (1) {
        pacer_wait();

        if (max_rows() < 0 && !hasEnded) {
            tinygl_text("GAME OVER!!!");
            hasEnded = true;
            ir_uart_putc('D');
        }

        if (hasEnded) {
            tinygl_update();
            led_on();
            continue;
        }

        led_off();
        display(&player, &obj);
        control(&player);

        if (equals(player, obj)) {
            ir_uart_putc('N');
            obj = point(rand() % (max_rows() + 1), rand() % (MAX_COL + 1));
        }


        if (ir_uart_read_ready_p()) {
            uint8_t res = ir_uart_getc();
            // If received signal, shrink the column
            switch (res) {
                case 'N':
                    shrink_rows(&player, &obj);
                    led_on();
                    break;
                case 'D':
                    tinygl_text("YOU WIN!!!");
                    hasEnded = true;
                default:
                    continue;
            }
        }

    }

    return 0;
}