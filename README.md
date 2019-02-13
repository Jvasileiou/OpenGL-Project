# OpenGL-Project
OpenGL - Glut project 

### Desription
The purpose of this project is to familiarize yourself with the use
basic libraries of elementary graphics such as Opengl / GLUT which
support both 2D and 3D graphics. 
It is small design program projects simple (non-self-defining) polygons. The program creates 
closed simple polygonal lines (non-autochthonous) which will then be cut off in a single rectangle
a cut-off parallelogram that will be parallel to the x and y axes. The cut one will give one or more
more simple (convex or non-convex) polygons. Finally these polygons will be made after normal
3D objects that the user can see by moving the camera to 3D. When
the program begins will open a 600 column column and 500 pixel lines of its
whose dimensions can not be changed.

##### Use : Hodgeman-Sutherland Algorithm

##### WARNING : The code is really unreadable. The project was created under the pressure and there was limited time!

### RUN only on LINUX (Ubuntu)
  $ sudo apt-get update   
  $ sudo apt-get install libglu1-mesa-dev freeglut3-dev mesa-common-dev

  ● MakeFile:       make PROG=xxxx    
   That xxxx is the name of the file will be compiled.

  ● Compile:
        g++ polygons.cpp triagulate.cpp -lGL -lGLU -lglut 

#### Authors 
1. John Vasileiou  
2. Periklis Ioannou
