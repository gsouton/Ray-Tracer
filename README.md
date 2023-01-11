# Ray-Tracer

![alt text](https://github.com/gsouton/Ray-Tracer/blob/main/github_docs/metal.png)


This project is a quick implementation of a raytracer, in C++.
It was implemented following the design implementation of [Ray Tracing in One Weekend, Peter Shirley](https://raytracing.github.io/books/RayTracingInOneWeekend.html)

## Use
### CMake
    `mkdir build`
    `cd build`
    `cmake ..`
    `make -j`
    `./main`

### Makefile
    `make`
    `./main`

Result should be written to the file `image.png`

## Goals

- Make use of modern C++.
- Learning about Ray tracing
- Having fun

## Future

- The code can be optimized
- We could a more intersting use of parallel computing
- We could introduce distributed computation (Maybe MPI)
