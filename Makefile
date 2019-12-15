PROGARM = main
CC = gcc
CFAGS = -g -Wall -I/usr/X11R6/include -I/usr/pkg/include
LDLIBS = -lGL -lGLU -lglut -lm

$(PROGARM): main.o image.o light.o
	$(CC) $(CFLAGS) -o $(PROGARM) image.o light.o main.o $(LDLIBS)

main.o: main.c main.h
	$(CC) $(CFLAGS) -c main.c -o main.o $(LDLIBS)

image.o: image.c image.h
	$(CC) $(CFLAGS) -c image.c $(LDLIBS)

light.o: light.c light.h
	$(CC) $(CFLAGS) -c light.c $(LDLIBS)

.PHONY: clean 

clean: 
	-rm *.o $(PROGRAM) *core
