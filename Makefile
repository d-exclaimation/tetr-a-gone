#
#  Makefile
#  
#  Makefile for the application
#
#  Authored by vno16 and ski102 on 30 Sep 2022
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
main.o: main.c ./vector2.h ./hexagone.h ./led.h ../../drivers/avr/pio.h ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

hexagone.o: hexagone.c hexagone.h ./vector2.h
	$(CC) -c $(CFLAGS) $< -o $@

vector2.o: vector2.c vector2.h
	$(CC) -c $(CFLAGS) $< -o $@

led.o: led.c led.h ../../drivers/avr/pio.h ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

pio.o: ../../drivers/avr/pio.c ../../drivers/avr/pio.h ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

system.o: ../../drivers/avr/system.c ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

# TODO: Add the new display, control, and communication module


# Link
main.out: main.o vector2.o hexagone.o led.o pio.o system.o
	$(CC) $(CFLAGS) $^ -o $@ -lm
	$(SIZE) $@


# Target: clean project
.PHONY: clean
clean:
		-$(DEL) *.o *.out *.hex


# Target: program project.
.PHONY: program
program: main.out
	$(OBJCOPY) -O ihex main.out main.hex
	dfu-programmer atmega32u2 erase; dfu-programmer atmega32u2 flash main.hex; dfu-programmer atmega32u2 start
