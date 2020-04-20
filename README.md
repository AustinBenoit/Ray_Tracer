# Ray Tracer
A ray tracer written in C++.

Renders an orthographic or prespective image. Can use point lights with matte materials. 

## Sample Images

<img src="/SampleImages/Orthographic.png" width="300"> <img src="/SampleImages/Matte.png" width="300"> 

<img src="/SampleImages/Phong.png" width="300"> <img src="/SampleImages/Reflective.png" width="300">

Top left is a basic orthographic render. Top Right is a perspective render with shadows and a matte like material. 
Bottom left is a perspective with phong shading. Bottom right is a perspective with reflective shading.

## Features
- Backward ray tracing
- Orthographic output
- Perspective output with a virtual camera
- Shadows
- Point Lights
- Ambient light
- Matte, Phong and reflective Shading

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
