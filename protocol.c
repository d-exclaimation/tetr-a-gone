//
//  protocol.c
//  hexagone
//
//  Created by vno16 on 11:44.
//

#include "protocol.h"

/** TODO: Update to use the current vector2 API */
static Point_t parse_packet(uint8_t packet)
{
    int8_t col = packet % 100 / 10;
    int8_t row = packet % 10;
    return invert(point(row, col));
}

void proto_init()
{
    ir_uart_init();
}

void proto_end(void)
{
    ir_uart_putc(CLOSING);
}

void proto_send(const Point_t point)
{
    uint8_t packet = 100 + point.col * 10 + point.row;
    ir_uart_putc(packet);
}

void proto_receive(Hexagone_t* game)
{
    if (!ir_uart_read_ready_p()) {
        return;
    }
    uint8_t received = ir_uart_getc();

    if (received == CLOSING) {
        game->state = DONE;
    } else if (received <= 146 && received >= 100) {
        Point_t other = parse_packet(received);
        floor_physics(game, other);
    }
}