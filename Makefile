# AUTHOR: Austin Benoit
# -I /usr/local/opt/boost
# Add in camera.o

CC            := g++
OPTIONS       := -std=c++14  -pedantic-errors -Wall -Wall -Werror -Wextra
INCLUDE       := -I /Ray_Tracer/

all: ray_tracer

ray_tracer: main.cpp BMP/bitmap_image.hpp  maths.o
	$(CC) main.cpp maths.o $(OPTIONS) $(INCLUDE) -o ray_tracer.out

maths.o: Maths/maths.hpp Maths/maths.cpp
	$(CC) $(OPTIONS) $(INCLUDE) -c Maths/maths.cpp

camera.o: maths.o Camera/camera.cpp Camera/camera.hpp
	$(CC) $(OPTIONS) $(INCLUDE) -c Camera/camera.cpp

clean:
	rm -r *.out 
	rm -r *.o