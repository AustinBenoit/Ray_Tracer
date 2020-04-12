# AUTHOR: Austin Benoit
#
#

CC            := g++
OPTIONS       := -std=c++14 -I /usr/local/opt/boost -pedantic-errors -Wall -Wall -Werror -Wextra -o

all: ray_tracer

ray_tracer: main.cpp BMP/bitmap_image.hpp
	$(CC) main.cpp $(OPTIONS) ray_tracer.out

clean:
	rm -r *.out