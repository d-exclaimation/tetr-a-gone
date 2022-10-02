//
//  protocol.h
//  hexagone
//
//  Created by vno16 on 11:59.
//

#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <limits.h>
#include "hexagone.h"
#include "ir_uart.h"

#define CLOSING 0xAA

void proto_init(void);
void proto_send(const Point_t point);
void proto_end(void);
void proto_receive(Hexagone_t* game);

#endif