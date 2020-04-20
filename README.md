# Ray Tracer
A ray tracer written in C++.

Renders an orthographic or prespective image. Can use point lights with matte materials. 

## Sample Images

<img src="/SampleImages/out.png" width="300"> <img src="/SampleImages/out_pinhole.png" width="300">

Left is a basic orthographic render. Right is a perspective render with shadows and a matte like material. 

## Features
- Backward ray tracing
- Orthographic output
- Perspective 0utput with a virtual camera
- Shadows
- Point Lights
- Ambient light

## Goals
- Impliments a simple UI interface to watch the render and a custom Ray Tracer.

## To Do:
- Adding in materials
- Adding in meshes
- Anti Aliasing
- Clean up and separate header files and cpp
- Add screen drawing in addition to saving the image.

## BMP Function
The bmp file save function is written by
Author: Arash Partow
URL: http://partow.net/programming/bitmap/index.html

## Requirements
Must have BOOST C++

## Build
Run make command
then run the executable "ray_tracer.out"
