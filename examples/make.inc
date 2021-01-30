MCU ?= attiny85
F_CPU ?= 8000000
SRC = ../../src
SOURCES := $(wildcard $(SRC)/*.c $(SRC)/*.cpp)
SKETCH := $(wildcard *.ino)

all:
	avr-gcc -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os -flto -I$(SRC) ../main.cpp $(SOURCES) -x c++ $(SKETCH) -o main.elf

