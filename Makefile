#
#  Makefile
#  ence260
#
#  Created by vno16 on 21:00.
#


# Definitions.
CC = avr-gcc
CFLAGS = -mmcu=atmega32u2 -Os -Wall -Wstrict-prototypes -Wextra -g -I../../drivers -I../../fonts -I../../drivers/avr -I../../utils
OBJCOPY = avr-objcopy
SIZE = avr-size
DEL = rm


# Default target.
all: main.out


# Compile
main.o: main.c ./point.h ./io.h # ./hexagone.h ./led.h ./io.h ../../drivers/avr/system.h ../../drivers/display.h ../../drivers/navswitch.h ../../fonts/font5x7_1.h ../../utils/font.h ../../utils/pacer.h ../../utils/tinygl.h
	$(CC) -c $(CFLAGS) $< -o $@

# io.o: io.c io.h ./hexagone.h ./point.h ../../drivers/avr/delay.h ../../drivers/avr/pio.h ../../drivers/avr/system.h ../../drivers/avr/timer.h ../../utils/pacer.h ../../drivers/ledmat.h 
# 	$(CC) -c $(CFLAGS) $< -o $@

# led.o: led.c led.h ../../drivers/avr/pio.h ../../drivers/avr/system.h
# 	$(CC) -c $(CFLAGS) $< -o $@

# pio.o: ../../drivers/avr/pio.c ../../drivers/avr/pio.h ../../drivers/avr/system.h
# 	$(CC) -c $(CFLAGS) $< -o $@

# system.o: ../../drivers/avr/system.c ../../drivers/avr/system.h
# 	$(CC) -c $(CFLAGS) $< -o $@

# timer.o: ../../drivers/avr/timer.c ../../drivers/avr/system.h ../../drivers/avr/timer.h
# 	$(CC) -c $(CFLAGS) $< -o $@

# display.o: ../../drivers/display.c ../../drivers/avr/system.h ../../drivers/display.h ../../drivers/ledmat.h
# 	$(CC) -c $(CFLAGS) $< -o $@

# ledmat.o: ../../drivers/ledmat.c ../../drivers/avr/pio.h ../../drivers/avr/system.h ../../drivers/ledmat.h
# 	$(CC) -c $(CFLAGS) $< -o $@

# navswitch.o: ../../drivers/navswitch.c ../../drivers/avr/delay.h ../../drivers/avr/pio.h ../../drivers/avr/system.h ../../drivers/navswitch.h
# 	$(CC) -c $(CFLAGS) $< -o $@

# font.o: ../../utils/font.c ../../drivers/avr/system.h ../../utils/font.h
# 	$(CC) -c $(CFLAGS) $< -o $@

# pacer.o: ../../utils/pacer.c ../../drivers/avr/system.h ../../drivers/avr/timer.h ../../utils/pacer.h
# 	$(CC) -c $(CFLAGS) $< -o $@

# tinygl.o: ../../utils/tinygl.c ../../drivers/avr/system.h ../../drivers/display.h ../../utils/font.h ../../utils/tinygl.h
# 	$(CC) -c $(CFLAGS) $< -o $@

# hexagone.o: hexagone.c hexagone.h ./point.h
# 	$(CC) -c $(CFLAGS) $< -o $@

point.o: point.c point.h
	$(CC) -c $(CFLAGS) $< -o $@

# Link
main.out: main.o led.o # io.o hexagone.o point.o pio.o system.o timer.o display.o ledmat.o navswitch.o font.o pacer.o tinygl.o
	$(CC) $(CFLAGS) $^ -o $@ -lm
	$(SIZE) $@


# Target: clean project.
.PHONY: clean
clean: 
	-$(DEL) *.o *.out *.hex


# Target: program project.
.PHONY: program
program: main.out
	$(OBJCOPY) -O ihex main.out main.hex
	dfu-programmer atmega32u2 erase; dfu-programmer atmega32u2 flash main.hex; dfu-programmer atmega32u2 start


