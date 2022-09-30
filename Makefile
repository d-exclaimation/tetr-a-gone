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
main.o: main.c ./vector2.h ./hexagone.h
	$(CC) -c $(CFLAGS) $< -o $@

vector2.o: vector2.c vector2.h
	$(CC) -c $(CFLAGS) $< -o $@


# Link
main.out: main.o vector2.o
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
