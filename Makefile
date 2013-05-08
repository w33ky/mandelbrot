CC = clang++
LIBS = -lGL -lGLU -lglut
CFLAGS = -Wall -O2

all: main.cpp
	$(CC) $(CFLAGS) $(LIBS) main.cpp -o mandelbrot



