//
//  communication.c
//  
//  Module for handling IR communications
//
//  Authored by vno16 and ski102 on 07 Oct 2022
//

#include "communication.h"


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

    
    led_on();

    Packet_t packet = ir_uart_getc();
    Message_t msg = message_decode(packet);
    switch (msg.typeno) {
        
        // Update the other player
        case PLAYER_POSITION:
            game->other = msg.payload;            
            break;

        case PLATFORM_FORCE:
            hexagone_physics(game, msg.payload);
            break;

        case GAME_OVER:
            game->state = hexagone_ended_p(game) ? game->state : WIN;
            break;

        default:
            break;
    }

    if (hexagone_fallen_p(game, game->player))
        comms_publish(message_end());
    
    hexagone_audit(game);
}