# AUTHOR: Austin Benoit
# -I /usr/local/opt/boost
# Add in camera.o

CC            := g++
OPTIONS       := -std=c++17  -pedantic-errors -Wall -Wall -Werror -Wextra 
INCLUDE       := -I Includes/

all: ray_tracer

ray_tracer: main.cpp maths.o geometricobject.o world.o
	$(CC) main.cpp maths.o geometricobject.o world.o \
		$(OPTIONS) -lc++ $(INCLUDE) -o ray_tracer.out

maths.o: Maths/maths.hpp Maths/maths.cpp
	$(CC) $(OPTIONS) $(INCLUDE) -c Maths/maths.cpp

camera.o: maths.o Camera/camera.cpp Camera/camera.hpp
	$(CC) $(OPTIONS) $(INCLUDE) -c Camera/camera.cpp

geometricobject.o: maths.o GeometricObject/geometricobject.hpp GeometricObject/geometricobject.cpp
	$(CC) $(OPTIONS) $(INCLUDE) -c GeometricObject/geometricobject.cpp

lights.o : Lights/lights.hpp Lights/lights.cpp
	$(CC) $(OPTIONS) $(INCLUDE) -c Lights/lights.cpp

brdf.o : maths.o BRDF/brdf.hpp BRDF/brdf.cpp
	$(CC) $(OPTIONS) $(INCLUDE) -c BRDF/brdf.cpp

world.o: camera.o lights.o geometricobject.o maths.o brdf.o
	$(CC) $(OPTIONS) $(INCLUDE) -c World/world.cpp

tracer.o: Tracer/tracer.hpp Tracer/tracer.cpp world.o
	$(CC) $(OPTIONS) $(INCLUDE) -c Tracer/tracer.cpp



clean:
	rm -r *.o
	rm -r *.out 
