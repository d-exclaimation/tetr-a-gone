//
//  communication.c
//  
//  Module for handling IR communications
//
//  Authored by Vincent ~ (vno16) and Natalie Kim (ski102) on 07 Oct 2022
//

#include "communication.h"


/**
 * @brief initialize communications
 */
void comms_init(void)
{
    ir_uart_init();
}

/**
 * @brief publish a message through infrared
 * 
 * @param msg the message being sent
 */
void comms_publish(const Message_t msg)
{
    Packet_t packet = message_encode(msg);
    ir_uart_putc(packet);
}

/**
 * @brief Redundantly publish a message through infrared to combat any losses
 * 
 * @param msg The message being sent
 */
void comms_redundant_publish(const Message_t msg)
{
    for (size_t i = 0; i < REDUNDANCY_LIMIT; i++) {
        comms_publish(msg);
    }
}

/**
 * @brief Subscribe to any incoming messages and apply changes to the game
 * 
 * @param game The game states
 */
void comms_subscribe(Tetragone_t* game)
{
    if (tetragone_ended_p(game) || !ir_uart_read_ready_p()) {
        return;
    }
    
    const Packet_t packet = ir_uart_getc();
    const Message_t msg = message_decode(packet);

    switch (msg.typeno) {
        
        // Update the other player
        case PLAYER_POSITION:
            game->other = msg.payload;            
            break;

        // Perform physics on the platform
        case PLATFORM_FORCE:
            tetragone_physics(game, msg.payload);
            break;

        // End the game if not ended already
        case GAME_OVER:
            game->state = tetragone_ended_p(game) ? game->state : WIN;
            break;

        default:
            return;
    }

    // Turn on LED everytime a valid message is received
    led_on();

    // Performs checks
    tetragone_audit(game);

    // Send an ending message
    // Done in excess to avoid game being out of sync
    // Should cause no other problems since ending is idempotent
    if (tetragone_ended_p(game)) {
        comms_redundant_publish(message_end());
    }
}