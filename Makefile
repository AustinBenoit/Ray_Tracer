# AUTHOR: Austin Benoit
#
#

CC            := g++
OPTIONS       := -std=c++14 -pedantic-errors -Wall -Wall -Werror -Wextra -o

all: ray_tracer

ray_tracer: test_main.cpp BMP/bitmap_image.hpp
	$(CC) test_main.cpp $(OPTIONS) ray_tracer.out

