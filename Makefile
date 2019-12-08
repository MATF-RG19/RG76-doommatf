PROGARM = main
CC = gcc
CFAGS = -g -Wall 
LDLIBS = -lGL -lGLU -lglut -lm

$(PROGARM): main.o image.o
	$(CC) $(CFLAGS) -o $(PROGARM) image.o main.o

main.o: main.c main.h
	$(CC) $(CFLAGS) -c main.c -o main.o $(LDLIBS)

image.o: image.c 
	$(CC) $(CFLAGS) -c image.c $(LDLIBS)
