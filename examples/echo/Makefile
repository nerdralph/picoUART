MCU ?= attiny13
F_CPU ?= 9600000
SRC = ../../src

all:
	avr-gcc -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os -flto -I$(SRC) ../main.cpp $(SRC)/*.{c,cpp} -x c++ *.ino -o main

