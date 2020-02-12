MCU ?= attiny13
F_CPU ?= 9600000

all:
	avr-gcc -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os -flto -I../.. main.c ../../*.c -x c *.ino -o main
