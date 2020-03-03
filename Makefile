# AUTHOR: Austin Benoit
#
#

CC            := g++
OPTIONS       := -std=c++14 -pedantic-errors -Wall -Wall -Werror -Wextra -o

all: ray_tracer

ray_tracer: test.cpp
	$(CC) test.cpp $(OPTIONS) ray_tracer

