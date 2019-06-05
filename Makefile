CC = g++
LIBS = -lGL -lGLU -lglut
CFLAGS = -Wall -O2

all: main.cpp
	$(CC) $(CFLAGS) main.cpp -o mandelbrot $(LIBS)



