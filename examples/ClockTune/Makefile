MCU ?= attiny13
F_CPU ?= 9600000
SRC = ../../src
SOURCES := $(wildcard $(SRC)/*.c $(SRC)/picoUART.cpp)
SKETCH := $(wildcard *.ino)

all:
	avr-gcc -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os -flto -I$(SRC) ../main.cpp $(SOURCES) -x c++ $(SKETCH) -o main

