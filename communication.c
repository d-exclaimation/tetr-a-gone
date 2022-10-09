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
    
    Packet_t packet = ir_uart_getc();
    Message_t msg = message_decode(packet);

    switch (msg.typeno) {
        
        // Update the other player
        case PLAYER_POSITION:
            game->other = msg.payload;            
            break;

        // Perform physics on the platform
        case PLATFORM_FORCE:
            hexagone_physics(game, msg.payload);
            break;

        // End the game if not ended already
        case GAME_OVER:
            game->state = hexagone_ended_p(game) ? game->state : WIN;
            break;

        default:
            return;
    }

    // Turn on LED everytime a valid message is received
    led_on();

    // Send an ending message if the player fell or had fallen after receiving a message
    if (hexagone_fallen_p(game, game->player)) {
        comms_publish(message_end());
    }
    
    // Performs checks
    hexagone_audit(game);
}