PROGARM = DoomMatf
CC = gcc
CFAGS = -g -Wall -I/usr/X11R6/include -I/usr/pkg/include
LDLIBS = -lGL -lGLU -lglut -lm

$(PROGARM): DoomMatf.o image.o light.o axis.o
	$(CC) $(CFLAGS) -o $(PROGARM) image.o light.o DoomMatf.o axis.o $(LDLIBS)

DoomMatf.o: src/DoomMatf.c src/DoomMatf.h
	$(CC) $(CFLAGS) -c src/DoomMatf.c -o DoomMatf.o $(LDLIBS)

image.o: src/image.c src/image.h
	$(CC) $(CFLAGS) -c src/image.c $(LDLIBS)

light.o: src/light.c src/light.h
	$(CC) $(CFLAGS) -c src/light.c $(LDLIBS)

axis.o: src/axis.c src/axis.h
	$(CC) $(CFLAGS) -c src/axis.c $(LDLIBS)
.PHONY: clean 

clean: 
	-rm *.o $(PROGRAM) *core
