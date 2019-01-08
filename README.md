# UC3M Computer Architecture 17/18 - Final Project
# Parallel programming assignment with OpenMP

## Authors
- Daniel Martín Blázquez
- Ramiro Pinto Prieto

## Description
In this lab assignment, we are requested to implement two versions of the same problem, the nasteroid problem, both written in the C++ programming language. The first will have a sequential execution, while the second one will use threads implemented using OpenMP to parallelize the execution and have a better performance. After that, we will evaluate the performance obtained in both versions and the speed up between the two.
The problem consists on a space with a maximum width and height given in which several asteroids and planets will be placed following random distributions given in the problem statement. Its masses will also follow these distributions. The asteroids will move due to the forces that each body exerts to the others in discrete and fixed intervals of time during a given number of iterations. After each movement of the asteroids, a laser ray, placed in a given y-coordinate, will be shot destroying any asteroid in the range of the width of the ray.
The program will print the initial configuration in a text file, where it will show the input parameters that were given to the problem, as well as the position and the masses of each asteroid and planet and the position of the ray. After every iteration has been performed, the program will print in another text file the final position, the velocities and the masses of all the asteroids that were not destroyed during the execution of the program.

