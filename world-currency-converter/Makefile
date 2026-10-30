# World Currency Converter - build file
CC      ?= gcc
CFLAGS  ?= -std=c99 -Wall -Wextra -pedantic -O2
TARGET   = currency_converter

all: $(TARGET)

$(TARGET): src/main.c src/rates.h
	$(CC) $(CFLAGS) -o $(TARGET) src/main.c -lm

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET) $(TARGET).exe

.PHONY: all run clean
