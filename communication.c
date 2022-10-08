//
//  communication.c
//  
//  Module for handling IR communications
//
//  Authored by vno16 and ski102 on 07 Oct 2022
//

#include "communication.h"


/*!
 * \brief Send an ending message if audit result in game ending after receiveing a message
 */
static void comms_end(void)
{
    comms_publish(message_end());
}

void comms_init(void)
{
    ir_uart_init();
}

void comms_publish(const Message_t msg)
{
    Packet_t packet = message_encode(msg);
    ir_uart_putc(packet);
}

void comms_subscribe(Hexagone_t* game)
{
    if (!ir_uart_read_ready_p()) {
        return;
    }

    Packet_t packet = ir_uart_getc();
    Message_t msg = message_decode(packet);
    switch (msg.typeno) {
        

        // Update the other player
        case PLAYER_POSITION:
            led_on();
            game->other = msg.payload;            
            break;

        case PLATFORM_FORCE:
            led_on();
            hexagone_physics(game, msg.payload);
            break;

        case GAME_OVER:
            led_on();
            game->state = WIN;
            break;

        default:
            break;

        hexagone_audit(game, &comms_end);
    }
}