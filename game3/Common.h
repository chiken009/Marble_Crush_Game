#ifndef COMMON_H
#define COMMON_H

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define NUM_FIGURE 7

#define BLOCK_SIZE 39

#define BLOCK_SPACING 1

#define WINDOW_WIDTH 350
#define WINDOW_HEIGHT 500

#define LEFT 1
#define RIGHT 2
#define UP 3
#define DOWN 4

#define EMPTY 0
#define circle_points 200
#define TRUE 1
#define FALSE 0
const   float col[7][3] = { {0,0,0}, {1,0,0}, {0,1,0}, {0,0,1}, {1,1,0}, {1,0,1}, {0.467, 0.533, 0.600} };
/*
const int image[7][4][2]={{{0,0},{0,1},{1,1},{1,0}},{{0,-1},{0,0},{0,1},{0,2}},
			  {{0,1},{-1,1},{-1,0},{-1,-1}},{{0,1},{1,1},{1,0},{1,-1}},
			  {{-1,1}, {-1,0}, {0,0}, {0,-1}},{{0,1},{0,0},{-1,0},{-1,-1}},
			  {{-1,0},{0,0},{1,0},{0,1}}};
			  */

const int image[2][2] = { {0,0},{0,1}};
const float GL_PI= 3.14;

struct Rectangle
{
  int left, right, top, bottom;
};





#endif
