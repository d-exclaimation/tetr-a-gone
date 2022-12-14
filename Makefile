#
#  Makefile
#  
#  Makefile for the application
#
#  Authored by Vincent ~ (vno16) and Natalie Kim (ski102) on 30 Sep 2022
#

# Definitions
CC = avr-gcc
CFLAGS = -mmcu=atmega32u2 -Os -Wall -Wstrict-prototypes -Wextra -g -I. -I../../drivers/avr -I../../extra -I../../utils -I../../fonts -I../../drivers
OBJCOPY = avr-objcopy
SIZE = avr-size
DEL = rm

# Default target.
all: main.out


# Compile
main.o: main.c ./vector2.h ./tetragone.h ./led.h ../../drivers/avr/pio.h ../../drivers/avr/system.h ./communication.h ./io.h ../../utils/task.h
	$(CC) -c $(CFLAGS) $< -o $@

tetragone.o: tetragone.c tetragone.h ./vector2.h
	$(CC) -c $(CFLAGS) $< -o $@

vector2.o: vector2.c vector2.h
	$(CC) -c $(CFLAGS) $< -o $@

led.o: led.c led.h ../../drivers/avr/pio.h ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

timer0.o: ../../drivers/avr/timer0.c ../../drivers/avr/bits.h ../../drivers/avr/prescale.h ../../drivers/avr/system.h ../../drivers/avr/timer0.h
	$(CC) -c $(CFLAGS) $< -o $@

usart1.o: ../../drivers/avr/usart1.c ../../drivers/avr/system.h ../../drivers/avr/usart1.h
	$(CC) -c $(CFLAGS) $< -o $@

prescale.o: ../../drivers/avr/prescale.c ../../drivers/avr/prescale.h ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

ir_uart.o: ../../drivers/avr/ir_uart.c ../../drivers/avr/ir_uart.h ../../drivers/avr/pio.h ../../drivers/avr/system.h ../../drivers/avr/timer0.h ../../drivers/avr/usart1.h
	$(CC) -c $(CFLAGS) $< -o $@

pio.o: ../../drivers/avr/pio.c ../../drivers/avr/pio.h ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

system.o: ../../drivers/avr/system.c ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

message.o: ./message.c ./message.h ./vector2.h
	$(CC) -c $(CFLAGS) $< -o $@

communication.o: ./communication.c ./communication.h ./tetragone.h ./message.h ../../drivers/avr/ir_uart.h ../../drivers/avr/pio.h ../../drivers/avr/system.h ./led.h
	$(CC) -c $(CFLAGS) $< -o $@

io.o: ./io.c ./io.h ./tetragone.h ../../drivers/navswitch.h ../../drivers/ledmat.h ../../drivers/avr/system.h ../../drivers/avr/pio.h ./communication.h ./message.h ../../utils/tinygl.h ../../fonts/font5x5_1.h
	$(CC) -c $(CFLAGS) $< -o $@

navswitch.o: ../../drivers/navswitch.c ../../drivers/navswitch.h ../../drivers/avr/delay.h ../../drivers/avr/pio.h ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

ledmat.o: ../../drivers/ledmat.c ../../drivers/ledmat.h ../../drivers/avr/pio.h ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

timer.o: ../../drivers/avr/timer.c ../../drivers/avr/timer.h ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

tinygl.o: ../../utils/tinygl.c ../../utils/tinygl.h ../../drivers/avr/system.h ../../drivers/display.h ../../utils/font.h
	$(CC) -c $(CFLAGS) $< -o $@

font.o: ../../utils/font.c ../../utils/font.h ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

display.o: ../../drivers/display.c ../../drivers/display.h ../../drivers/avr/system.h ../../drivers/ledmat.h
	$(CC) -c $(CFLAGS) $< -o $@

task.o: ../../utils/task.c ../../drivers/avr/system.h ../../drivers/avr/timer.h ../../utils/task.h
	$(CC) -c $(CFLAGS) $< -o $@


# Link
main.out: main.o vector2.o tetragone.o led.o pio.o system.o ir_uart.o timer0.o usart1.o prescale.o message.o communication.o io.o navswitch.o ledmat.o timer.o tinygl.o font.o display.o task.o
	$(CC) $(CFLAGS) $^ -o $@ -lm
	$(SIZE) $@

# Package
main.hex: main.out
	$(OBJCOPY) -O ihex $< $@

# Target: clean project
.PHONY: clean
clean:
	-$(DEL) -f *.o *.out *.hex

# Target: test project
.PHONY: test
test:
	chmod +x ./test.sh
	./test.sh	

# Target: clean build project.
.PHONY: fresh
fresh: clean all

# Target: build, export, run project.
.PHONY: program
program: main.hex
	dfu-programmer atmega32u2 erase; dfu-programmer atmega32u2 flash main.hex; dfu-programmer atmega32u2 start

# Target: clean, build, export, and run project.
.PHONY: prod
prod: clean program
