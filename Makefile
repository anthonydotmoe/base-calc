all: main.c
	tigcc -O2 -Wall main.c hardware.c format.c draw.c -o base
