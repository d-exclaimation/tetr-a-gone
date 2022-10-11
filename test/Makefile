#
#  Makefile
#  
#  Makefile for testing
#
#  Authored by Vincent ~ (vno16) and Natalie Kim (ski102) on 07 Oct 2022
#

# Definitions
CC = gcc
CFLAGS = -Os -Wall -Wstrict-prototypes -Wextra -g -I. -I..
DEL = rm

# Default target.
all: test.out


# Compile
test.o: test.c ../vector2.h ../tetragone.h ../message.h ./unittest.h
	$(CC) -c $(CFLAGS) $< -o $@

unittest.o: ./unittest.c ./unittest.h
	$(CC) -c $(CFLAGS) $< -o $@

tetragone.o: ../tetragone.c ../tetragone.h ../vector2.h
	$(CC) -c $(CFLAGS) $< -o $@

vector2.o: ../vector2.c ../vector2.h
	$(CC) -c $(CFLAGS) $< -o $@

message.o: ../message.c ../message.h ../vector2.h
	$(CC) -c $(CFLAGS) $< -o $@


# Link
test.out: test.o vector2.o tetragone.o message.o unittest.o
	$(CC) $(CFLAGS) $^ -o $@ -lm


# Target: clean project
.PHONY: clean
clean:
		-$(DEL) *.o *.out *.hex


# Target: test project.
.PHONY: test
test: clean all
	./test.out
