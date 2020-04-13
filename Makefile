# AUTHOR: Austin Benoit
# -I /usr/local/opt/boost
#

CC            := g++
OPTIONS       := -std=c++14  -pedantic-errors -Wall -Wall -Werror -Wextra

all: ray_tracer

ray_tracer: main.cpp BMP/bitmap_image.hpp  maths.o
	$(CC) main.cpp maths.o $(OPTIONS) -o ray_tracer.out

maths.o: Maths/maths.hpp Maths/maths.cpp
	$(CC) $(OPTIONS) -c Maths/maths.cpp

clean:
	rm -r *.out 
	rm -r *.o