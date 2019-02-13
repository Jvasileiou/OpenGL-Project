// Ioannis Vasileiou 2647
// Periklis Ioannou 2880

// ------- INCLUDES ---------

//#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <GL/gl.h>    // Open Graphics Library (OpenGL) header
#include <GL/glu.h>   // glut header
#include <GL/glut.h>  // The GL Utility Toolkit (GLUT) Header
#include "triangulate.h"

// ============= DEFINE MICRO-PRO =============
// ------ ACTION MENU ------
#define POLYGON  1
#define CLIPPING 2
#define EXTRUDE  3
#define EXIT 	 4
// ------ COLORS ------
#define WHITE 1		// {1.0, 1.0, 1.0}
#define BLACK 2		// {0.0, 0.0, 0.0}
#define DARKGREY 3      // {0.4, 0.4, 0.4}
#define RED 4 		// {1.0, 0.0, 0.0}
#define GREEN 5 	// {0.0, 1.0, 0.0}
#define BLUE 6    	// {0.0, 0.0, 1.0}
#define CYAN 7  	// {0.0, 1.0, 1.0}
#define MAGENTA 8    	// {1.0, 0.0, 1.0}
#define YELLOW 9  	// {1.0, 1.0, 0.0}
#define DARKED 10  	// {0.5, 0.0, 0.0}
#define DARKGREEN 11	// {0.0, 0.5, 0.0}
#define DARKBLUE 12  	// {0.0, 0.0, 0.5}
#define DARKCYAN 13 	// {0.0, 0.5, 0.5}
#define DARKMAGENTA 14  // {0.5, 0.0, 0.5}
#define DARKYELLOW 15  	// {0.5, 0.5, 0.0}
#define LIGHTGREY 16	// {0.8, 0.8, 0.8}
//--------BONUS-----------
#define EXTRUSION_POLYGON 1
#define MOVE_A_POINT 2

// ============= END DEFINE MICRO-PRO =============
//
//
// =============  DEFINE FUNCTIONS =============

void resize(int width, int height);
void goToFillColorMenuEvent(int option);
void goToLineColorMenuEvent(int option);
void goToActionMenuEvent(int option);
void createMenu();
void createPoints(int z);
void createLines(int z);
void createLastLine(int z);
void mouseButton(int button, int state, int x, int y);
void display();
void takeTheTrianglePoints(int points);
void createPolygon();
int IsPointInBoundingBox(float x1, float y1, float x2, float y2, float px, float py);
int LineIntersection( float l1x1, float l1y1, float l1x2, float l1y2,
                            float l2x1, float l2y1, float l2x2, float l2y2,
                            float *m1, float *c1, float *m2, float *c2,
                            float* intersection_X, float* intersection_Y );
int LineSegmentIntersection(float l1x1, float l1y1, float l1x2, float l1y2,
														                            float l2x1, float l2y1, float l2x2, float l2y2,
														                            float *m1, float *c1, float *m2, float *c2,
														                            float* intersection_X, float* intersection_Y);
int checkIfThereIsIntersection(int numberOfPolygons);
void createTriangulate(int p);
void keyboard(unsigned char key, int x, int y);
int checkIfThereIsIntersectionWithTheLastLine();



void createAllClippingPolygons();
void createClippingPolygon();
void isRigth(int cX1, int cX2, int cY1, int cY2,
                        int X1, int Y1, int X2,
                              int Y2, int *a, int *b,
                            int *c, int *d);
void LineIntersection2(double l1x1, double l1y1, double l1x2, double l1y2,
                      double l2x1, double l2y1, double l2x2, double l2y2,
                          double* intersection_X, double* intersection_Y);
void isDown(int cX1, int cX2, int cY1, int cY2,
                    int X1, int Y1, int X2,
                      int Y2, int *a, int *b,
                      int *c, int *d);
void isLeft(int cX1, int cX2, int cY1, int cY2,
                          int X1, int Y1, int X2,
                          int Y2, int *a, int *b,
                          int *c, int *d);
void isUp(int cX1, int cX2, int cY1, int cY2,
                    int X1, int Y1, int X2,
                    int Y2, int *a, int *b,
                    int *c, int *d);
void putTheElementsInArray(int* counterForArray,int *a,int *b,int *c,int *d);
void takeTheTrianglePointsForClippingArray(int counterForArray, int polygonNumber);
void displayClipingPolygonPoints(int t);
void displayClipingPolygonLines(int t);
void displayClipingPolygonNames(int t);
void displayClipingPolygons();
void displayClipingPolygonTriangulate(int t);
void takeTheCordOfClipingOrtho(int x, int y);
void changeSize(int w, int h);

// ============= END FUNCTIONS =============
//
//
//
//
//
//
// ============= GLOBAL =============

typedef struct POINTS{
	int x;
	int y;
}Point;

typedef struct TRIANGLE{
	int x;
	int y;
}Triangle;

typedef struct Polygons{
	Point arrayPoints[100];
	Triangle arrayTrianglePoints[100];
  float colorLineArray[3];
  float colorFillArray[3];
	int numOfPoints;
	int pointsForTriangle;
  int extrusion;
}Polygons;

Polygons polygons[100];

typedef struct Clipping{
  Point arrayPoints[100];
  Triangle arrayTrianglePoints[100];
  int cord[4][2];
  float colorFillArray[3];
  float colorLineArray[3];
  int pointsForTriangle;
  int numOfPoints;
}Clipping;

Clipping clippingArray[100];

using namespace std;
int numberOfPolygons = -1;
float colorFillArray[3]={1.0, 1.0, 1.0};
int counter = 0;
int exitOfPolygon = 0;
int counterForT = 0;
int polygonNumber = 0;
int showPolygonsAsTriangles = 0;

int movePoint = 0;
int moveCounter = 0;
int moveX = 0;
int moveY = 0;
int numberOfMovePoint = 0;


int extrudeBtn = 0 ;


int clippingBtn = 0;
int clippingPoints = 0;
int exitOfClippingPoint = 0;
int clippingCord = 0;
int fx;
int fy ;
int sx;
int sy ;
int a = 0;
int b = 0;
int c = 0;
int d = 0;
int array[100][2];
int array2[100][2];
int bonus1 = 0 ;
int i,y,x, k ,l ,j;

GLfloat xRotated, yRotated, zRotated;

// ============= END GLOBAL =============

void resize(int width, int height)
{
	// we ignore the params and do:
  if(extrudeBtn == 0 ){
	   glutReshapeWindow(600, 500);
  }else{
    changeSize(width, height);
  }
}

void goToFillColorMenuEvent(int option)
{
	if(option == WHITE)
	{
		polygons[ numberOfPolygons + 1 ].colorFillArray[0] = 1.0;
		polygons[ numberOfPolygons + 1 ].colorFillArray[1] = 1.0;
		polygons[ numberOfPolygons + 1 ].colorFillArray[2] = 1.0;
	}
	else if(option == BLACK)
	{
		polygons[ numberOfPolygons + 1 ].colorFillArray[0] = 0.0;
		polygons[ numberOfPolygons + 1 ].colorFillArray[1] = 0.0;
		polygons[ numberOfPolygons + 1 ].colorFillArray[2] = 0.0;
	}
	else if(option == DARKGREY)
	{
		polygons[ numberOfPolygons + 1 ].colorFillArray[0] = 0.4;
		polygons[ numberOfPolygons + 1 ].colorFillArray[1] = 0.4;
		polygons[ numberOfPolygons + 1 ].colorFillArray[2] = 0.4;
	}
	else if(option == RED)
	{
		polygons[ numberOfPolygons + 1 ].colorFillArray[0] = 1.0;
		polygons[ numberOfPolygons + 1 ].colorFillArray[1] = 0.0;
		polygons[ numberOfPolygons + 1 ].colorFillArray[2] = 0.0;
	}
	else if(option == GREEN)
	{
		polygons[ numberOfPolygons + 1 ].colorFillArray[0] = 0.0;
		polygons[ numberOfPolygons + 1 ].colorFillArray[1] = 1.0;
		polygons[ numberOfPolygons + 1 ].colorFillArray[2] = 0.0;
	}
	else if(option == BLUE)
	{
		polygons[ numberOfPolygons + 1 ].colorFillArray[0] = 0.0;
		polygons[ numberOfPolygons + 1 ].colorFillArray[1] = 0.0;
		polygons[ numberOfPolygons + 1 ].colorFillArray[2] = 1.0;
	}
	else if(option == CYAN)
	{
		polygons[ numberOfPolygons + 1 ].colorFillArray[0] = 0.0;
		polygons[ numberOfPolygons + 1 ].colorFillArray[1] = 1.0;
		polygons[ numberOfPolygons + 1 ].colorFillArray[2] = 1.0;
	}
	else if(option == MAGENTA)
	{
		polygons[ numberOfPolygons + 1 ].colorFillArray[0] = 1.0;
		polygons[ numberOfPolygons + 1 ].colorFillArray[1] = 0.0;
		polygons[ numberOfPolygons + 1 ].colorFillArray[2] = 1.0;
	}
	else if(option == YELLOW)
	{
		polygons[ numberOfPolygons + 1 ].colorFillArray[0] = 1.0;
		polygons[ numberOfPolygons + 1 ].colorFillArray[1] = 1.0;
		polygons[ numberOfPolygons + 1 ].colorFillArray[2] = 0.0;
	}
	else if(option == DARKED)
	{
		polygons[ numberOfPolygons + 1 ].colorFillArray[0] = 0.5;
		polygons[ numberOfPolygons + 1 ].colorFillArray[1] = 0.0;
		polygons[ numberOfPolygons + 1 ].colorFillArray[2] = 0.0;
	}
	else if(option == DARKGREEN)
	{
		polygons[ numberOfPolygons + 1 ].colorFillArray[0] = 0.0;
		polygons[ numberOfPolygons + 1 ].colorFillArray[1] = 0.5;
		polygons[ numberOfPolygons + 1 ].colorFillArray[2] = 0.0;
	}
	else if(option == DARKBLUE)
	{
		polygons[ numberOfPolygons + 1 ].colorFillArray[0] = 0.0;
		polygons[ numberOfPolygons + 1 ].colorFillArray[1] = 0.0;
		polygons[ numberOfPolygons + 1 ].colorFillArray[2] = 0.5;
	}
	else if(option == DARKCYAN)
	{
		polygons[ numberOfPolygons + 1 ].colorFillArray[0] = 0.0;
		polygons[ numberOfPolygons + 1 ].colorFillArray[1] = 0.5;
		polygons[ numberOfPolygons + 1 ].colorFillArray[2] = 0.5;
	}
	else if(option == DARKMAGENTA)
	{
		polygons[ numberOfPolygons + 1 ].colorFillArray[0] = 0.5;
		polygons[ numberOfPolygons + 1 ].colorFillArray[1] = 0.0;
		polygons[ numberOfPolygons + 1 ].colorFillArray[2] = 0.5;
	}
	else if(option == DARKYELLOW)
	{
		polygons[ numberOfPolygons + 1 ].colorFillArray[0] = 0.5;
		polygons[ numberOfPolygons + 1 ].colorFillArray[1] = 0.5;
		polygons[ numberOfPolygons + 1 ].colorFillArray[2] = 0.0;
	}
	else if(option == LIGHTGREY)
	{
		polygons[ numberOfPolygons + 1 ].colorFillArray[0] = 0.8;
		polygons[ numberOfPolygons + 1 ].colorFillArray[1] = 0.8;
		polygons[ numberOfPolygons + 1 ].colorFillArray[2] = 0.8;
	}

	return;
}

void goToLineColorMenuEvent(int option)
{
	if(option == WHITE)
	{
		polygons[ numberOfPolygons + 1 ].colorLineArray[0] = 1.0;
		polygons[ numberOfPolygons + 1 ].colorLineArray[1] = 1.0;
		polygons[ numberOfPolygons + 1 ].colorLineArray[2] = 1.0;
	}
	else if(option == BLACK)
	{
		polygons[ numberOfPolygons + 1 ].colorLineArray[0] = 0.0;
		polygons[ numberOfPolygons + 1 ].colorLineArray[1] = 0.0;
		polygons[ numberOfPolygons + 1 ].colorLineArray[2] = 0.0;
	}
	else if(option == DARKGREY)
	{
		polygons[ numberOfPolygons + 1 ].colorLineArray[0] = 0.4;
		polygons[ numberOfPolygons + 1 ].colorLineArray[1] = 0.4;
		polygons[ numberOfPolygons + 1 ].colorLineArray[2] = 0.4;
	}
	else if(option == RED)
	{
		polygons[ numberOfPolygons + 1 ].colorLineArray[0] = 1.0;
		polygons[ numberOfPolygons + 1 ].colorLineArray[1] = 0.0;
		polygons[ numberOfPolygons + 1 ].colorLineArray[2] = 0.0;
	}
	else if(option == GREEN)
	{
		polygons[ numberOfPolygons + 1 ].colorLineArray[0] = 0.0;
		polygons[ numberOfPolygons + 1 ].colorLineArray[1] = 1.0;
		polygons[ numberOfPolygons + 1 ].colorLineArray[2] = 0.0;
	}
	else if(option == BLUE)
	{
		polygons[ numberOfPolygons + 1 ].colorLineArray[0] = 0.0;
		polygons[ numberOfPolygons + 1 ].colorLineArray[1] = 0.0;
		polygons[ numberOfPolygons + 1 ].colorLineArray[2] = 1.0;
	}
	else if(option == CYAN)
	{
		polygons[ numberOfPolygons + 1 ].colorLineArray[0] = 0.0;
		polygons[ numberOfPolygons + 1 ].colorLineArray[1] = 1.0;
		polygons[ numberOfPolygons + 1 ].colorLineArray[2] = 1.0;
	}
	else if(option == MAGENTA)
	{
		polygons[ numberOfPolygons + 1 ].colorLineArray[0] = 1.0;
		polygons[ numberOfPolygons + 1 ].colorLineArray[1] = 0.0;
		polygons[ numberOfPolygons + 1 ].colorLineArray[2] = 1.0;
	}
	else if(option == YELLOW)
	{
		polygons[ numberOfPolygons + 1 ].colorLineArray[0] = 1.0;
		polygons[ numberOfPolygons + 1 ].colorLineArray[1] = 1.0;
		polygons[ numberOfPolygons + 1 ].colorLineArray[2] = 0.0;
	}
	else if(option == DARKED)
	{
		polygons[ numberOfPolygons + 1 ].colorLineArray[0] = 0.5;
		polygons[ numberOfPolygons + 1 ].colorLineArray[1] = 0.0;
		polygons[ numberOfPolygons + 1 ].colorLineArray[2] = 0.0;
	}
	else if(option == DARKGREEN)
	{
		polygons[ numberOfPolygons + 1 ].colorLineArray[0] = 0.0;
		polygons[ numberOfPolygons + 1 ].colorLineArray[1] = 0.5;
		polygons[ numberOfPolygons + 1 ].colorLineArray[2] = 0.0;
	}
	else if(option == DARKBLUE)
	{
		polygons[ numberOfPolygons + 1 ].colorLineArray[0] = 0.0;
		polygons[ numberOfPolygons + 1 ].colorLineArray[1] = 0.0;
		polygons[ numberOfPolygons + 1 ].colorLineArray[2] = 0.5;
	}
	else if(option == DARKCYAN)
	{
		polygons[ numberOfPolygons + 1 ].colorLineArray[0] = 0.0;
		polygons[ numberOfPolygons + 1 ].colorLineArray[1] = 0.5;
		polygons[ numberOfPolygons + 1 ].colorLineArray[2] = 0.5;
	}
	else if(option == DARKMAGENTA)
	{
		polygons[ numberOfPolygons + 1 ].colorLineArray[0] = 0.5;
		polygons[ numberOfPolygons + 1 ].colorLineArray[1] = 0.0;
		polygons[ numberOfPolygons + 1 ].colorLineArray[2] = 0.5;
	}
	else if(option == DARKYELLOW)
	{
		polygons[ numberOfPolygons + 1 ].colorLineArray[0] = 0.5;
		polygons[ numberOfPolygons + 1 ].colorLineArray[1] = 0.5;
		polygons[ numberOfPolygons + 1 ].colorLineArray[2] = 0.0;
	}
	else if(option == LIGHTGREY)
	{
		polygons[ numberOfPolygons + 1 ].colorLineArray[0] = 0.8;
		polygons[ numberOfPolygons + 1 ].colorLineArray[1] = 0.8;
		polygons[ numberOfPolygons + 1 ].colorLineArray[2] = 0.8;
	}

	return;
}

// -----------------------------------------------------
// -----------------------------------------------------
// ++++++++++++++++++++	INTERSECTION  ++++++++++++++++++
// -----------------------------------------------------
// -----------------------------------------------------



int IsPointInBoundingBox(float x1, float y1, float x2, float y2, float px, float py)
{
    float left, top, right, bottom;
    if(x1 < x2)
    {
        left = x1;
        right = x2;
        //printf("x1 < x2 \n");
    }
    else
    {
        left = x2;
        right = x1;
        //printf("x1 > x2 \n");
    }
    if(y1 < y2)
    {
        top = y1;
        bottom = y2;
        //printf("y1 < y2 \n");
    }
    else
    {
        top = y1;
        bottom = y2;
        //printf("y1 > y2 \n");
    }

    if( (px+0.01) >= left && (px-0.01) <= right ||
            (py+0.01) >= top && (py-0.01) <= bottom )
    {
    	//printf("IsPointInBoundingBox ----- return 1 -------"  );
        return 1;
    }
    else
    	//printf("IsPointInBoundingBox ----- return 0 -------"  );
        return 0;
}

int LineIntersection( float l1x1, float l1y1, float l1x2, float l1y2,
                            float l2x1, float l2y1, float l2x2, float l2y2,
                            float *m1, float *c1, float *m2, float *c2,
                            float* intersection_X, float* intersection_Y )
{
    float dx, dy;

    dx = l1x2 - l1x1;
    dy = l1y2 - l1y1;
    *m1 = dy / dx;
    *c1 = l1y1 - *m1 * l1x1;

    dx = l2x2 - l2x1;
    dy = l2y2 - l2y1;
    *m2 = dy / dx;
    *c2 = l2y1 - *m2 * l2x1;

    if( (*m1 - *m2) == 0){
        //printf("LineIntersection ----- return 0 -------"  );
        return 0;
    }
    else
    {
        *intersection_X = (*c2 - *c1) / (*m1 - *m2);
        *intersection_Y = *m1 * *intersection_X + *c1;
    }
}

int LineSegmentIntersection(float l1x1, float l1y1, float l1x2, float l1y2,
                            float l2x1, float l2y1, float l2x2, float l2y2,
                            float *m1, float *c1, float *m2, float *c2,
                            float* intersection_X, float* intersection_Y)
{
    float dx, dy;

    dx = l1x2 - l1x1;
    dy = l1y2 - l1y1;
    *m1 = dy / dx;
    *c1 = l1y1 - *m1 * l1x1;

    dx = l2x2 - l2x1;
    dy = l2y2 - l2y1;
    *m2 = dy / dx;
    *c2 = l2y1 - *m2 * l2x1;

    if( (*m1 - *m2) == 0){
    	//printf("LineSegmentIntersection ----- return == 0 -------"  );
        return 0;
    }else
    {
        *intersection_X = (*c2 - *c1) / (*m1 - *m2);
        *intersection_Y = *m1 * *intersection_X + *c1;
    }
    if(IsPointInBoundingBox(l1x1, l1y1, l1x2, l1y2, *intersection_X, *intersection_Y) == 1 &&
    	        IsPointInBoundingBox(l2x1, l2y1, l2x2, l2y2, *intersection_X, *intersection_Y) == 1)
    {
		//printf("IsPointInBoundingBox --- MPIKA"  );
		return 1;
    }
    else{

        return 0;
    }
}

int checkIfThereIsIntersection(int numberOfPolygons)
{
	// m = klisi
	// c = diakladwsi
	float m1, c1, m2, c2;
    float l1x1, l1y1, l1x2, l1y2;
    float l2x1, l2y1, l2x2, l2y2;
    float intersection_X, intersection_Y;
    int nRet;

    // The cordinates of the new line
    l1x1 = (float) polygons[numberOfPolygons].arrayPoints[ polygons[numberOfPolygons].numOfPoints -1].x ;
    l1y1 = (float) polygons[numberOfPolygons].arrayPoints[ polygons[numberOfPolygons].numOfPoints -1].y ;
    l1x2 = (float) polygons[numberOfPolygons].arrayPoints[ polygons[numberOfPolygons].numOfPoints -2].x ;
    l1y2 = (float) polygons[numberOfPolygons].arrayPoints[ polygons[numberOfPolygons].numOfPoints -2].y ;

    int max = polygons[numberOfPolygons].numOfPoints - 3; // 2(not connected line) + 1 (because counter++) => 3
    for(int i = max ; i > 0 ; i--)
    {
    	l2x1 = (float) (polygons[numberOfPolygons].arrayPoints[i].x) ;
	    l2y1 = (float) (polygons[numberOfPolygons].arrayPoints[i].y) ;
	    l2x2 = (float) (polygons[numberOfPolygons].arrayPoints[i-1].x) ;
	    l2y2 = (float) (polygons[numberOfPolygons].arrayPoints[i-1].y) ;

	    nRet = LineSegmentIntersection(l1x1, l1y1, l1x2, l1y2,
                            			l2x1, l2y1, l2x2, l2y2,
                            			&m1, &c1, &m2, &c2, &intersection_X, &intersection_Y);
      /*
		  printf("---------------------------\n") ;
	    printf("m1 = %.2f \n" , m1 );
	    printf("c1 = %.2f \n" , c1 );
   		printf("m2 = %.2f \n" , m2 );
   		printf("c2 = %.2f \n" , c2 );

		printf("\nEquation of line1: Y = %.2fX %c %.2f\n", m1, (c1 < 0) ? ' ' : '+',  c1);

 	    printf("\nEquation of line2: Y = %.2fX %c %.2f\n", m2, (c2 < 0) ? ' ' : '+',  c2);


	    printf("---------------------------\n\n") ;
   		printf("nRet = %d \n\n" , nRet );
 	    printf("---------------------------\n") ;
      */
		if(nRet == 1)
    	{
    	    printf("The two line segments intersect each other at %.2f, %.2f \n", intersection_X, intersection_Y);
			return 1 ;
   		}
	}
   	return 0;
}


int checkIfThereIsIntersectionWithTheLastLine()
{

  // m = klisi
	// c = diakladwsi
	float m1, c1, m2, c2;
    float l1x1, l1y1, l1x2, l1y2;
    float l2x1, l2y1, l2x2, l2y2;
    float intersection_X, intersection_Y;
    int nRet = 0;

    // The Last Point
    l1x1 = (float) polygons[numberOfPolygons].arrayPoints[ polygons[numberOfPolygons].numOfPoints -1].x ;
    l1y1 = (float) polygons[numberOfPolygons].arrayPoints[ polygons[numberOfPolygons].numOfPoints -1].y ;
    // The First Point
    l1x2 = (float) polygons[numberOfPolygons].arrayPoints[0].x ;
    l1y2 = (float) polygons[numberOfPolygons].arrayPoints[0].y ;

    int max = polygons[numberOfPolygons].numOfPoints - 2; // 2(not connected line) + 1 (because counter++) => 3
    for(int i = max ; i > 1 ; i--)
    {

	    l2x1 = (float) (polygons[numberOfPolygons].arrayPoints[i].x) ;
		l2y1 = (float) (polygons[numberOfPolygons].arrayPoints[i].y) ;
		l2x2 = (float) (polygons[numberOfPolygons].arrayPoints[i-1].x) ;
		l2y2 = (float) (polygons[numberOfPolygons].arrayPoints[i-1].y) ;

	    nRet = LineSegmentIntersection(l1x1, l1y1, l1x2, l1y2,
	                           			l2x1, l2y1, l2x2, l2y2,
	                           			&m1, &c1, &m2, &c2, &intersection_X, &intersection_Y);

		if(nRet == 1)
    	{
    	    printf("The two line segments intersect each other at %.2f, %.2f \n", intersection_X, intersection_Y);
			return 1 ;
   		}

		}

	return 0;
}

// -----------------------------------------------------
// -----------------------------------------------------
// ++++++++++++++++++++	END OF INTERSECTION  ++++++++++++++++++
// -----------------------------------------------------
// -----------------------------------------------------


void goToActionMenuEvent(int option)
{
	if(option == POLYGON)
	{
		exitOfPolygon = 0;
		numberOfPolygons += 1;
        clippingBtn = 0;
		polygons[numberOfPolygons].numOfPoints = 0;
		glutMouseFunc(mouseButton);
	}
	else if(option == CLIPPING)
	{
		clippingBtn = 1;
    	glutMouseFunc(mouseButton);
	}
	else if(option == EXTRUDE)
	{
		extrudeBtn = 1;
		glutMouseFunc(mouseButton);
	}
	else if(option == EXIT)
	{
		exit(0);
	}
}

void goToBonusMenuEvent(int option)
{
  if(option == EXTRUSION_POLYGON)
	{
    bonus1 = 1;
  }
  else if(option == MOVE_A_POINT)
  {
    movePoint = 1;
    moveCounter = 0;
    glutMouseFunc(mouseButton);
  }
}

void createMenu()
{
	int mainMenu, bonusMenu, actionMenu, lineColorMenu, fillColorMenu;
  //BONUS
  bonusMenu = glutCreateMenu(goToBonusMenuEvent);
	glutAddMenuEntry("EXTRUSION OF EACH POLYGON", 1);
	glutAddMenuEntry("MOVE A POINT", 2);

	// ACTION
	actionMenu = glutCreateMenu(goToActionMenuEvent);
	glutAddMenuEntry("POLYGON", 1);
	glutAddMenuEntry("CLIPPING", 2);
	glutAddMenuEntry("EXTRUDE", 3);
	glutAddMenuEntry("EXIT", 4);

	// LINE COLOR
	lineColorMenu = glutCreateMenu(goToLineColorMenuEvent);
	glutAddMenuEntry("WHITE", 1);
  	glutAddMenuEntry("BLACK", 2);
	glutAddMenuEntry("DARKGREY", 3);
	glutAddMenuEntry("RED", 4);
	glutAddMenuEntry("GREEN", 5);
	glutAddMenuEntry("BLUE", 6);
	glutAddMenuEntry("CYAN", 7);
	glutAddMenuEntry("MAGENTA", 8);
	glutAddMenuEntry("YELLOW", 9);
	glutAddMenuEntry("DARKED", 10);
	glutAddMenuEntry("DARKGREEN", 11);
	glutAddMenuEntry("DARKBLUE", 12);
	glutAddMenuEntry("DARKCYAN", 13);
	glutAddMenuEntry("DARKYELLOW", 14);
	glutAddMenuEntry("LIGHTGREY", 15);


	// FILL COLOR
	fillColorMenu = glutCreateMenu(goToFillColorMenuEvent);
	glutAddMenuEntry("WHITE", 1);
  	glutAddMenuEntry("BLACK", 2);
	glutAddMenuEntry("DARKGREY", 3);
	glutAddMenuEntry("RED", 4);
	glutAddMenuEntry("GREEN", 5);
	glutAddMenuEntry("BLUE", 6);
	glutAddMenuEntry("CYAN", 7);
	glutAddMenuEntry("MAGENTA", 8);
	glutAddMenuEntry("YELLOW", 9);
	glutAddMenuEntry("DARKED", 10);
	glutAddMenuEntry("DARKGREEN", 11);
	glutAddMenuEntry("DARKBLUE", 12);
	glutAddMenuEntry("DARKCYAN", 13);
	glutAddMenuEntry("DARKYELLOW", 14);
	glutAddMenuEntry("LIGHTGREY", 15);
	// MAIN MENU
	mainMenu=glutCreateMenu(goToActionMenuEvent);
  	glutAddSubMenu("ACTION", actionMenu);
  	glutAddSubMenu("LINE_COLOR", lineColorMenu);
  	glutAddSubMenu("FILL_COLOR", fillColorMenu);
    glutAddSubMenu("BONUS", bonusMenu);
	// Right Click to OPEN the main menu
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void takeTheCordOfClipingOrtho(int x, int y)
{
  clippingCord++;
  if(clippingCord == 1){
    fx = x;
    fy = 500 - y;

  }else if (clippingCord == 2){
    sx = x;
    sy = 500 - y;
    if( fx > sx ){
      //   |    -->left
      clippingArray[ 0 ].cord[ 0 ][ 0 ] = sx;
      //    -   -->  Top
      clippingArray[ 0 ].cord[ 1 ][ 0 ] = sx;
      //     |  -->right
      clippingArray[ 0 ].cord[ 2 ][ 0 ] = fx;
      //    _  -->bottom
      clippingArray[ 0 ].cord[ 3 ][ 0 ] = fx;
    }else{

      clippingArray[ 0 ].cord[ 0 ][ 0 ] = fx;
      clippingArray[ 0 ].cord[ 1 ][ 0 ] = fx;
      clippingArray[ 0 ].cord[ 2 ][ 0 ] = sx;
      clippingArray[ 0 ].cord[ 3 ][ 0 ] = sx;
    }
    if( fy > sy ){
      clippingArray[ 0 ].cord[ 0 ][ 1 ] = sy;
      clippingArray[ 0 ].cord[ 1 ][ 1 ] = fy;
      clippingArray[ 0 ].cord[ 2 ][ 1 ] = fy;
      clippingArray[ 0 ].cord[ 3 ][ 1 ] = sy;
    }else{
      clippingArray[ 0 ].cord[ 0 ][ 1 ] = fy;
      clippingArray[ 0 ].cord[ 1 ][ 1 ] = sy;
      clippingArray[ 0 ].cord[ 2 ][ 1 ] = sy;
      clippingArray[ 0 ].cord[ 3 ][ 1 ] = fy;
    }
  }
}

// -----------------------------------------------------
// -----------------------------------------------------
// ++++++++++++++++++++	START BONUS MOVE POINT  ++++++++++++++++++
// -----------------------------------------------------
// -----------------------------------------------------

void takeTheMovePoint(int x, int y)
{

  int numberOfPoints = polygons[ 0 ].numOfPoints;
  for( int i = 0; i < numberOfPoints; i++)
  {
      if( ( (polygons[0].arrayPoints[ i ].x + 10) > x) && ( x > (polygons[0].arrayPoints[ i ].x - 10) )
          && ( (polygons[0].arrayPoints[ i ].y + 10) > y) && ( y > (polygons[0].arrayPoints[ i ].y - 10) ) )
          {
            moveX = polygons[0].arrayPoints[ i ].x;
            moveY = polygons[0].arrayPoints[ i ].y;
            numberOfMovePoint = i;
            printf("\n%d\n",numberOfMovePoint );
            break;
          }
  }
  moveCounter++;
}

int intersectionMovePoint(int afterX1, int afterY1, int x1, int y1, int startPoint, int finishPoint)
{
  float m1, c1, m2, c2;
  float intersection_X, intersection_Y;
  float l2x1, l2y1, l2x2, l2y2;
  int nRet = 0;
  for( int i = startPoint; i < finishPoint; i++)
  {
      l2x1 = (float) (polygons[0].arrayPoints[i].x) ;
      l2y1 = (float) (polygons[0].arrayPoints[i].y) ;
      l2x2 = (float) (polygons[0].arrayPoints[i+1].x) ;
      l2y2 = (float) (polygons[0].arrayPoints[i+1].y + 1) ;

      nRet = LineSegmentIntersection(afterX1, afterY1, x1, y1,
                                  l2x1, l2y1, l2x2, l2y2,
                                  &m1, &c1, &m2, &c2, &intersection_X, &intersection_Y);
      if(nRet == 1)
      {
        printf("The two line segments intersect each other at %.2f, %.2f \n", intersection_X, intersection_Y);
        return 1;
      }
  }
  return 0;
}

int intersectionMovePoint1(int afterX1, int afterY1, int x1, int y1, int startPoint, int finishPoint)
{
  float m1, c1, m2, c2;
  float intersection_X, intersection_Y;
  float l2x1, l2y1, l2x2, l2y2;
  int nRet = 0;
  int start = startPoint;
  int sNext = startPoint + 1;
  for( int i = 0 ; i < polygons[0].numOfPoints - 3; i++)
  {
    if( start == polygons[0].numOfPoints ){
      start = 0;
    }
    if( sNext == polygons[0].numOfPoints ){
      sNext = 0;
    }

    l2x1 = (float) (polygons[0].arrayPoints[start].x) ;
    l2y1 = (float) (polygons[0].arrayPoints[start].y ) ;
    l2x2 = (float) (polygons[0].arrayPoints[sNext].x) ;
    l2y2 = (float) (polygons[0].arrayPoints[sNext].y ) ;

    nRet = LineSegmentIntersection(afterX1, afterY1, x1, y1,
                                l2x1, l2y1, l2x2, l2y2,
                                &m1, &c1, &m2, &c2, &intersection_X, &intersection_Y);
    sNext++;
    start++;
    if(nRet == 1)
    {
      printf("The two line segments intersect each other at %.2f, %.2f \n", intersection_X, intersection_Y);
      return 1;
    }
  }
  return 0;

}

void checkIfThereIsIntersectionForTheMovePoint(int x, int y)
{

    int nRet = 0;

    int prevX = 0;
    int prevY = 0;
    int afterX = 0;
    int afterY = 0;
    //Triangle < 3
    if( polygons[0].numOfPoints > 3)
    {
      //CHECK IF IT IS THE FIRST POINT
      if( numberOfMovePoint == 0 )
      {
        prevX = (float) polygons[0].arrayPoints[ polygons[ 0 ].numOfPoints - 1 ].x;
        prevY = (float) polygons[0].arrayPoints[ polygons[ 0 ].numOfPoints - 1 ].y;

        afterX = (float) polygons[0].arrayPoints[ numberOfMovePoint + 1 ].x;
        afterY = (float) polygons[0].arrayPoints[ numberOfMovePoint + 1 ].y;

        nRet = intersectionMovePoint(afterX, afterY, x, y, 2, polygons[ 0 ].numOfPoints - 1);
        if(nRet == 1)
        {
          return;
        }
        nRet = intersectionMovePoint(x, y, prevX, prevY, 1, polygons[ 0 ].numOfPoints - 2);

        if(nRet == 0)
        {
          polygons[ 0 ].arrayPoints[ numberOfMovePoint ].x = x;
          polygons[ 0 ].arrayPoints[ numberOfMovePoint ].y = y;
        }



      }
      //CHECK IF IT IS THE LAST POINT
      else if ( numberOfMovePoint == (polygons[ 0 ].numOfPoints - 1) )
      {
        prevX = polygons[0].arrayPoints[ numberOfMovePoint - 1 ].x;
        prevY = polygons[0].arrayPoints[ numberOfMovePoint - 1 ].y;

        afterX = polygons[0].arrayPoints[ 0 ].x;
        afterY = polygons[0].arrayPoints[ 0 ].y;

        nRet = intersectionMovePoint(afterX, afterY, x, y, 1, polygons[ 0 ].numOfPoints - 2);
        if(nRet == 1)
        {
          return;
        }
        nRet = intersectionMovePoint(x, y, prevX, prevY, 0, polygons[ 0 ].numOfPoints - 3);
        if(nRet == 0)
        {
          polygons[ 0 ].arrayPoints[ numberOfMovePoint ].x = x;
          polygons[ 0 ].arrayPoints[ numberOfMovePoint ].y = y;
        }
      }
      else if ( numberOfMovePoint == 1 )
      {
        prevX = polygons[0].arrayPoints[ numberOfMovePoint - 1 ].x;
        prevY = polygons[0].arrayPoints[ numberOfMovePoint - 1 ].y;

        afterX = polygons[0].arrayPoints[ numberOfMovePoint + 1 ].x;
        afterY = polygons[0].arrayPoints[ numberOfMovePoint + 1 ].y;

        nRet = intersectionMovePoint1(afterX, afterY, x, y, numberOfMovePoint + 2, 0);
        if(nRet == 1)
        {
          return;
        }
        nRet = intersectionMovePoint1(x, y, prevX, prevY, numberOfMovePoint + 1, polygons[ 0 ].numOfPoints - 1);
        if(nRet == 0)
        {
          polygons[ 0 ].arrayPoints[ numberOfMovePoint ].x = x;
          polygons[ 0 ].arrayPoints[ numberOfMovePoint ].y = y;
        }
      }
      else if ( numberOfMovePoint == (polygons[ 0 ].numOfPoints - 2) )
      {
        prevX = polygons[0].arrayPoints[ numberOfMovePoint - 1 ].x;
        prevY = polygons[0].arrayPoints[ numberOfMovePoint - 1 ].y;

        afterX = polygons[0].arrayPoints[ numberOfMovePoint + 1 ].x;
        afterY =  polygons[0].arrayPoints[ numberOfMovePoint + 1 ].y;

        nRet = intersectionMovePoint1(afterX, afterY, x, y, 0, numberOfMovePoint - 1);
        if(nRet == 1)
        {
          return;
        }
        nRet = intersectionMovePoint1(x, y, prevX, prevY, polygons[ 0 ].numOfPoints - 1, numberOfMovePoint - 2);
        if(nRet == 0)
        {
          polygons[ 0 ].arrayPoints[ numberOfMovePoint ].x = x;
          polygons[ 0 ].arrayPoints[ numberOfMovePoint ].y = y;
        }
      }
      //OTHER POINT
      else
      {
        prevX = polygons[0].arrayPoints[ numberOfMovePoint - 1 ].x;
        prevY = polygons[0].arrayPoints[ numberOfMovePoint - 1 ].y;

        afterX = polygons[0].arrayPoints[ numberOfMovePoint + 1 ].x;
        afterY = polygons[0].arrayPoints[ numberOfMovePoint + 1 ].y;
        nRet = intersectionMovePoint1(afterX, afterY, x, y, numberOfMovePoint + 2, numberOfMovePoint - 1);
        if(nRet == 1)
        {
          return;
        }
        nRet = intersectionMovePoint1(x, y, prevX, prevY, numberOfMovePoint +1, numberOfMovePoint - 2);
        if(nRet == 0)
        {
          polygons[ 0 ].arrayPoints[ numberOfMovePoint ].x = x;
          polygons[ 0 ].arrayPoints[ numberOfMovePoint ].y = y;
        }
      }
    }
    else
    {
        polygons[ 0 ].arrayPoints[ numberOfMovePoint ].x = x;
        polygons[ 0 ].arrayPoints[ numberOfMovePoint ].y = y;
    }

    takeTheTrianglePoints( polygons[0].numOfPoints );

}

// -----------------------------------------------------
// -----------------------------------------------------
// ++++++++++++++++++++	END BONUS MOVE POINT  ++++++++++++++++++
// -----------------------------------------------------
// -----------------------------------------------------



// -----------------------------------------------------
// -----------------------------------------------------
// ++++++++++++++++++++	E X T R U D E  ++++++++++++++++++
// -----------------------------------------------------
// -----------------------------------------------------


// actual vector representing the camera's direction
float lx=0.0f, lz=-100.0f;
// XZ position of the camera
float exx=0.0f, exy=1.0f ,exz=50.0f;

// all variables initialized to 1.0, meaning
// the triangle will initially be white
float red=1.0f, blue=1.0f, green=1.0f;

// angle for rotating triangle
float angle = 0.0f;
int mikosExothisis;
int exothisi=0;

/* Initialize OpenGL Graphics */
void initGL()
 {
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
   glClearDepth(10.0f);                   // Set background depth to farthest

}

void display3d() {

  if(exothisi == 0){
    if(bonus1 == 1){
      for(int i=0; i<numberOfPolygons+1; i++){
        printf("\nGive extrution length of %d polygon ",i);
        scanf("%d",&polygons[i].extrusion);
      }
    }
    else
    {
      printf("\nGive length of extrusion ");
      scanf("%d",&mikosExothisis);
      for(int i = 0; i<numberOfPolygons+1 ; i++){
        polygons[i].extrusion= mikosExothisis;
      }
    }
    exothisi++;
  }

   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
   glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix
   glLoadIdentity();                 // Reset the model-view matrix

   gluLookAt(exx, exy, exz,
    exx + lx, exy , exz + lz,
    0.0f , 1.0f, 0.0f
    );

    // Draw ground
    glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_QUADS);
    glVertex3f(-100.0f, 0.0f, -100.0f);
    glVertex3f(-100.0f, 0.0f, 100.0f);
    glVertex3f( 100.0f, 0.0f, 100.0f);
    glVertex3f( 100.0f, 0.0f, -100.0f);
    glEnd();

    glColor3f(1.0f, 1.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex3f(-100.0f, 600.0f, -100.0f);
    glVertex3f(-100.0f, 600.0f, 100.0f);
    glVertex3f( 100.0f, 600.0f, 100.0f);
    glVertex3f( 100.0f, 600.0f, -100.0f);
    glEnd();



    for(int k = 0 ; k < numberOfPolygons+1 ; k++)
    {
		for(int i = 0 ; i < polygons[0].pointsForTriangle-1 ; i += 3 )
		{
    		// Render a color-cube consisting of 6 quads with different colors

			glTranslatef(0.0f, 0.0f, 0.0f);  // Move right and into the screen




		    int x1 = polygons[k].arrayTrianglePoints[i].x;
		    int y1 = polygons[k].arrayTrianglePoints[i].y;
		    int x2 = polygons[k].arrayTrianglePoints[i+1].x;
		    int y2 = polygons[k].arrayTrianglePoints[i+1].y;
		    int x3 = polygons[k].arrayTrianglePoints[i+2].x;
		    int y3 = polygons[k].arrayTrianglePoints[i+2].y;

        // --------- 3 points ---------
            glBegin(GL_TRIANGLE_STRIP);

             // Back face (z = -z)
             glColor3f(polygons[k].colorLineArray[0], polygons[k].colorLineArray[1], polygons[k].colorLineArray[2]);     // Red
              glVertex3f( x1,  y1, -polygons[k].extrusion);
              glVertex3f( x2,  y2, -polygons[k].extrusion);
              glVertex3f( x3,  y3, -polygons[k].extrusion);

              glEnd();

              glBegin(GL_QUAD_STRIP) ;
              //glBegin(GL_QUADS) ;

              // Right face (x = 1.0f)
              glColor3f(polygons[k].colorFillArray[0], polygons[k].colorFillArray[1], polygons[k].colorFillArray[2]);     // Blue
              glVertex3f( x3, y3,  0.0f);
              glVertex3f( x1, y1,  0.0f);
              glVertex3f( x3, y3, -polygons[k].extrusion);
              glVertex3f( x1, y1, -polygons[k].extrusion);

              glEnd();  // End of drawing color-cube

		      // --------- 4 points ---------


		      glBegin(GL_QUAD_STRIP) ;
			 //glBegin(GL_QUADS) ;

		      // Bottom face (y = -1.0f)
          glColor3f(polygons[k].colorFillArray[0], polygons[k].colorFillArray[1], polygons[k].colorFillArray[2]);     // Blue
		      glVertex3f( x1, y1,  0.0f);
		      glVertex3f( x2, y2,  0.0f);
		      glVertex3f( x1, y1, -polygons[k].extrusion);
		      glVertex3f( x2, y2, -polygons[k].extrusion);

          glEnd();  // End of drawing color-cube
          glBegin(GL_QUAD_STRIP) ;
          //glBegin(GL_QUADS) ;

		      // Left face (x = -1.0f)
		       glColor3f(polygons[k].colorFillArray[0], polygons[k].colorFillArray[1], polygons[k].colorFillArray[2]);     // Blue
		      glVertex3f( x2, y2,  0.0f);
		      glVertex3f( x3, y3,  0.0f);
		      glVertex3f( x2, y2, -polygons[k].extrusion);
		      glVertex3f( x3, y3, -polygons[k].extrusion);

          glEnd();  // End of drawing color-cube


                    //Front face  (z = +z)
                    glBegin(GL_TRIANGLE_STRIP);

                        glColor3f(polygons[k].colorLineArray[0], polygons[k].colorLineArray[1], polygons[k].colorLineArray[2]);     // Red
                        glVertex3f( x1,  y1, 0.0f);
                        glVertex3f( x2,  y2, 0.0f);
                        glVertex3f( x3,  y3, 0.0f);

                        glEnd();





   		}
	}


}


void changeSize(int w, int h) {

  // Prevent a divide by zero, when window is too short
  // (you cant make a window of zero width).
  if (h == 0)
    h = 1;
    float ratio = w * 1.0 / h;

    // Use the Projection Matrix
    glMatrixMode(GL_PROJECTION);

    // Reset Matrix
    glLoadIdentity();

    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);

    // Set the correct perspective.
    gluPerspective(45.0f, ratio, 0.1f, 100.0f);

    // Get Back to the Modelview
    glMatrixMode(GL_MODELVIEW);
}


void expandTheTriangles()
{
  initGL();
	resize(600,500); // Register callback handler for window re-size event
	display3d();     // Register callback handler for window re-paint event
	glutPostRedisplay();

	return;
}


void processSpecialKeys(int key, int xx, int yy)
{

  float fraction = 5.0f;

  switch (key) {
    case GLUT_KEY_LEFT :
    angle -= 0.01f;
    lx = sin(angle);
    lz = -cos(angle);
    break;

    case GLUT_KEY_RIGHT :
    angle += 0.01f;
    lx = sin(angle);
    lz = -cos(angle);
    break;

    case GLUT_KEY_UP :
    exx += lx * fraction;
    exz += lz * fraction;
    break;

    case GLUT_KEY_DOWN :
    exx -= lx * fraction;
    exz -= lz * fraction;
    break;

    case GLUT_KEY_F1 :
    printf("MPOASDIGF\n\n\n");
    exy += 10;
    break;

    case GLUT_KEY_HOME :

    exy -= 10;
    break;

  }
}

// -----------------------------------------------------
// -----------------------------------------------------
// ++++++++++++++++++++ END   E X T R U D E  ++++++++++++++++++
// -----------------------------------------------------
// -----------------------------------------------------

void mouseButton(int button, int state, int x, int y)
{

	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
	    if( clippingBtn == 0 )
	    {
		      if( movePoint == 0 )
		      {
		    		// Add the coordinates of the current point
		    		polygons[numberOfPolygons].arrayPoints[ polygons[numberOfPolygons].numOfPoints ].x = x;
		    		polygons[numberOfPolygons].arrayPoints[ polygons[numberOfPolygons].numOfPoints ].y = 500 - y;
		    		polygons[numberOfPolygons].numOfPoints += 1;
		      }
		      else
		      {
		        //Bonus move a point
		        if( moveCounter == 0 ){
		          takeTheMovePoint(x, 500 - y);
		        }
		        else
		        {
		          checkIfThereIsIntersectionForTheMovePoint(x, 500 - y);
		          movePoint = 0;
		        }
		      }

	    }
	    else{
		      //draw the cliiping ortho
		      takeTheCordOfClipingOrtho(x, y);

	    }

	// Else IF there are only two points, it does not
	// enable the user to press the right button
		if (polygons[numberOfPolygons].numOfPoints >= 3 || clippingPoints >=3 )
		{   // Detach the rigth button until you finish your polygon
		    glutDetachMenu(GLUT_RIGHT_BUTTON);
		}
	}
	else if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
	  	if( checkIfThereIsIntersectionWithTheLastLine() != 1 )
	  	{
			// Last line
			exitOfPolygon = 1;
	       	glutMouseFunc(NULL);
			// Attach Menu to the right click for the menu options
			glutAttachMenu(GLUT_RIGHT_BUTTON);
		}
	}

	glutPostRedisplay();
	return;
}

void createPoints(int num, int numPoints)
{
	//create Points
	glColor3f(0.00, 0.00, 0.00);
	glPointSize(2.0f);
	glBegin(GL_POINTS);
	for (k = 0; k < numPoints; k++)
	{
		x = polygons[num].arrayPoints[k].x;
		y = polygons[num].arrayPoints[k].y;
		glVertex3f(x, y, 0);
	}
	glEnd();
}

void createLines(int num, int numPoints)
{
	if(numPoints>1 )
	{
		glLineWidth(2);
		glColor3f(polygons[ num ].colorLineArray[0],
              polygons[ num ].colorLineArray[1],
              polygons[ num ].colorLineArray[2]);

		glBegin(GL_LINES);
		//draw line to this points
		for(k = 0; k < numPoints-1; k++ )
		{
			 glVertex3f(polygons[num].arrayPoints[k].x, polygons[num].arrayPoints[k].y, 0);
			 glVertex3f(polygons[num].arrayPoints[k+1].x, polygons[num].arrayPoints[k+1].y, 0);
		}
		glEnd();
	}
}

void createLastLine(int num)
{
		glLineWidth(2);
    	glColor3f(polygons[ num ].colorLineArray[0],
              polygons[ num ].colorLineArray[1],
              polygons[ num ].colorLineArray[2]);

		glBegin(GL_LINES);
		glVertex3f(polygons[num].arrayPoints[0].x, polygons[num].arrayPoints[0].y, 0);
		glVertex3f(polygons[num].arrayPoints[ polygons[num].numOfPoints - 1].x, polygons[num].arrayPoints[ polygons[num].numOfPoints -1].y, 0);
		glEnd();
}


void createTriangulate(int p)
{
	glLineWidth(1);
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINES);
	for( l = 0; l < polygons[p].pointsForTriangle - 1; l+=3 )
	{
			glVertex3f(polygons[p].arrayTrianglePoints[l].x, polygons[p].arrayTrianglePoints[l].y, 0);
			glVertex3f(polygons[p].arrayTrianglePoints[l+1].x, polygons[p].arrayTrianglePoints[l+1].y, 0);
			glVertex3f(polygons[p].arrayTrianglePoints[l].x, polygons[p].arrayTrianglePoints[l].y, 0);
			glVertex3f(polygons[p].arrayTrianglePoints[l+2].x, polygons[p].arrayTrianglePoints[l+2].y, 0);
			glVertex3f(polygons[p].arrayTrianglePoints[l+1].x, polygons[p].arrayTrianglePoints[l+1].y, 0);
			glVertex3f(polygons[p].arrayTrianglePoints[l+2].x, polygons[p].arrayTrianglePoints[l+2].y, 0);
	}
	glEnd();
}

void paintPolygon(int num, int numPoints)
{
  glColor3f(polygons[ num ].colorFillArray[0],
            polygons[ num ].colorFillArray[1],
            polygons[ num ].colorFillArray[2]);

  for(int k = 0; k < polygons[num].pointsForTriangle - 1; k+=3 )
  {
    glBegin(GL_POLYGON);
     glVertex3f(polygons[num].arrayTrianglePoints[k].x, polygons[num].arrayTrianglePoints[k].y, 0 );
     glVertex3f(polygons[num].arrayTrianglePoints[k+1].x, polygons[num].arrayTrianglePoints[k+1].y, 0 );

     glVertex3f(polygons[num].arrayTrianglePoints[k+1].x, polygons[num].arrayTrianglePoints[k+1].y, 0 );
     glVertex3f(polygons[num].arrayTrianglePoints[k+2].x, polygons[num].arrayTrianglePoints[k+2].y, 0 );

     glVertex3f(polygons[num].arrayTrianglePoints[k+2].x, polygons[num].arrayTrianglePoints[k+2].y, 0 );
     glVertex3f(polygons[num].arrayTrianglePoints[k].x, polygons[num].arrayTrianglePoints[k].y, 0 );
     glEnd();
  }

}


void createPolygon()
{
	//IF THERE IS ANOTHER POLYGON
	if(numberOfPolygons > 0)
	{
		//DISPLAY ALL THE POLYGONS
		for(i = 0; i < numberOfPolygons; i++)
		{
			createPoints(i, polygons[i].numOfPoints);
			//IF T KEY PRESSED ---- 0 = FALSE --- 1 = TRUE ---
			if( showPolygonsAsTriangles == 0)
			{
				createLines(i, polygons[i].numOfPoints);
				createLastLine(i);
        		paintPolygon(i, polygons[numberOfPolygons].numOfPoints);
			}
			else
			{
				//CREATE TRIANGLE THE OTHER POLYGONS
				createTriangulate(i);
			}
		}
	}
	//THE POLYGON THAT I AM CREATING NOW
	createPoints(numberOfPolygons, polygons[numberOfPolygons].numOfPoints);
	if( showPolygonsAsTriangles == 0)
	{
		if(polygons[numberOfPolygons].numOfPoints >= 4 )
		{
			// NOW we need to check if there will be an intersection
			if( checkIfThereIsIntersection(numberOfPolygons) == 1 )
			{
				polygons[numberOfPolygons].numOfPoints-- ;
			}
		}

		createLines(numberOfPolygons, polygons[numberOfPolygons].numOfPoints);
		if(exitOfPolygon == 1)
		{
			createLastLine(numberOfPolygons);

			takeTheTrianglePoints( polygons[numberOfPolygons].numOfPoints );
      paintPolygon(numberOfPolygons, polygons[numberOfPolygons].numOfPoints);
      //glutMouseFunc(NULL);
		}
	}
	else
	{
		createTriangulate(numberOfPolygons);
	}

}

void takeTheTrianglePoints(int points)
{
	int tcount;
	Vector2dVector a;
	Vector2dVector result;
	for(int i = 0; i < points; i++ )
	{
		a.push_back( Vector2d(polygons[numberOfPolygons].arrayPoints[i].x, polygons[numberOfPolygons].arrayPoints[i].y) );
	}
	//  Invoke the triangulator to triangulate this polygon.
	Triangulate::Process(a,result);

	// print out the results.
	tcount = result.size()/3;
	polygons[numberOfPolygons].pointsForTriangle = result.size();
	y=0;
	for (int i=0; i<tcount; i++)
	{
		const Vector2d &p1 = result[i*3+0];
		const Vector2d &p2 = result[i*3+1];
		const Vector2d &p3 = result[i*3+2];
		polygons[numberOfPolygons].arrayTrianglePoints[y].x = p1.GetX();
		polygons[numberOfPolygons].arrayTrianglePoints[y].y = p1.GetY();
		y++;
		polygons[numberOfPolygons].arrayTrianglePoints[y].x = p2.GetX();
		polygons[numberOfPolygons].arrayTrianglePoints[y].y = p2.GetY();
		y++;
		polygons[numberOfPolygons].arrayTrianglePoints[y].x = p3.GetX();
		polygons[numberOfPolygons].arrayTrianglePoints[y].y = p3.GetY();
		y++;

	}
}

void takeTheTrianglePointsForClippingArray(int points, int polygonNumber)
{
	int tcount;
	Vector2dVector a;
	Vector2dVector result;
	for(int i = 0; i < points; i++ )
	{
		a.push_back( Vector2d(clippingArray[ polygonNumber ].arrayPoints[ i ].x, clippingArray[polygonNumber].arrayPoints[i].y) );
	}
	//  Invoke the triangulator to triangulate this polygon.
	Triangulate::Process(a,result);

	// print out the results.
	tcount = result.size()/3;
	clippingArray[ polygonNumber ].pointsForTriangle = result.size();
	y=0;
	for (int i=0; i<tcount; i++)
	{
		const Vector2d &p1 = result[i*3+0];
		const Vector2d &p2 = result[i*3+1];
		const Vector2d &p3 = result[i*3+2];
		clippingArray[ polygonNumber ].arrayTrianglePoints[ y ].x = p1.GetX();
		clippingArray[ polygonNumber ].arrayTrianglePoints[ y ].y = p1.GetY();
		y++;
		clippingArray[ polygonNumber ].arrayTrianglePoints[ y ].x = p2.GetX();
		clippingArray[ polygonNumber ].arrayTrianglePoints[ y ].y = p2.GetY();
		y++;
		clippingArray[ polygonNumber ].arrayTrianglePoints[ y ].x = p3.GetX();
		clippingArray[ polygonNumber ].arrayTrianglePoints[ y ].y = p3.GetY();
		y++;

	}
}

void createClippingPolygon()
{
    //DISPLAY THE ORTHO
    //create Points
    glColor3f(0.00, 0.00, 0.00);
    glPointSize(10.0f);
    glBegin(GL_POINTS);

    glVertex3f(clippingArray[ 0 ].cord[ 0 ][ 0 ], clippingArray[ 0 ].cord[ 0 ][ 1 ] , 0);
    glVertex3f(clippingArray[ 0 ].cord[ 1 ][ 0 ], clippingArray[ 0 ].cord[ 1 ][ 1 ] , 0);
    glVertex3f(clippingArray[ 0 ].cord[ 2 ][ 0 ], clippingArray[ 0 ].cord[ 2 ][ 1 ] , 0);
    glVertex3f(clippingArray[ 0 ].cord[ 3 ][ 0 ], clippingArray[ 0 ].cord[ 3 ][ 1 ] , 0);

    glEnd();


    glLineWidth(2);
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    //draw line to this points
    glVertex3f(clippingArray[ 0 ].cord[ 0 ][ 0 ], clippingArray[ 0 ].cord[ 0 ][ 1 ] , 0);
    glVertex3f(clippingArray[ 0 ].cord[ 1 ][ 0 ], clippingArray[ 0 ].cord[ 1 ][ 1 ] , 0);

    glVertex3f(clippingArray[ 0 ].cord[ 1 ][ 0 ], clippingArray[ 0 ].cord[ 1 ][ 1 ] , 0);
    glVertex3f(clippingArray[ 0 ].cord[ 2 ][ 0 ], clippingArray[ 0 ].cord[ 2 ][ 1 ] , 0);

    glVertex3f(clippingArray[ 0 ].cord[ 2 ][ 0 ], clippingArray[ 0 ].cord[ 2 ][ 1 ] , 0);
    glVertex3f(clippingArray[ 0 ].cord[ 3 ][ 0 ], clippingArray[ 0 ].cord[ 3 ][ 1 ] , 0);

    glVertex3f(clippingArray[ 0 ].cord[ 3 ][ 0 ], clippingArray[ 0 ].cord[ 3 ][ 1 ] , 0);
    glVertex3f(clippingArray[ 0 ].cord[ 0 ][ 0 ], clippingArray[ 0 ].cord[ 0 ][ 1 ] , 0);

    glEnd();


    createAllClippingPolygons();


}

void LineIntersection2(double l1x1, double l1y1, double l1x2, double l1y2,
                            double l2x1, double l2y1, double l2x2, double l2y2,
                            double* intersection_X, double* intersection_Y)
{
    // Line AB represented as a1x + b1y = c1
    double a1 = l1y2 - l1y1;
    double b1 = l1x1 - l1x2;
    double c1 = a1*(l1x1) + b1*(l1y1);

    // Line CD represented as a2x + b2y = c2
    double a2 = l2y2 - l2y1;
    double b2 = l2x1 - l2x2;
    double c2 = a2*(l2x1)+ b2*(l2y1);



    double determinant = a1*b2 - a2*b1;

    if (determinant == 0)
    {
        // The lines are parallel. This is simplified
        // by returning a pair of FLT_MAX
    }
    else
    {
        *intersection_X = (b2*c1 - b1*c2)/determinant;
        *intersection_Y = (a1*c2 - a2*c1)/determinant;
    }
}

void isRigth(int cX1, int cX2, int cY1, int cY2,
                      int X1, int Y1, int X2,
                      int Y2, int *a, int *b,
                      int *c, int *d)
{

    double intersection_X = 0.0, intersection_Y = 0.0;
    int nRet;
    double l1x1 = (double) cX1;
    double l1y1 = (double) cY1;
    double l1x2 = (double) cX2;
    double l1y2 = (double) cY2;
    double l2x1 = (double) X1;
    double l2y1 = (double) Y1;
    double l2x2 = (double) X2;
    double l2y2 = (double) Y2;

  if( (X1 >= cX1) && (X2 >= cX1) ){
    *a = X2;
    *b = Y2;
    *c = 0;
    *d = 0;
  }else if( (X1 < cX1) && (X2 < cX1) ){
    *a = 0;
    *b = 0;
    *c = 0;
    *d = 0;
  }else if( (X1 >= cX1) && (X2 < cX1) ){
    LineIntersection2(l1x1, l1y1, l1x2, l1y2,
                                l2x1, l2y1, l2x2, l2y2,
                               &intersection_X, &intersection_Y);
    *a = (int) round(intersection_X);
    *b = (int) round(intersection_Y);
    *c = 0;
    *d = 0;
  }else if( (X1 < cX1) && (X2 >= cX1) ){
    LineIntersection2(l1x1, l1y1, l1x2, l1y2,
                                l2x1, l2y1, l2x2, l2y2,
                               &intersection_X, &intersection_Y);
    *a = (int) round(intersection_X);
    *b = (int) round(intersection_Y);
    *c = X2;
    *d = Y2;
  }

}

void isDown(int cX1, int cX2, int cY1, int cY2,
                        int X1, int Y1, int X2,
                              int Y2, int *a, int *b,
                            int *c, int *d)
{

      double intersection_X = 0.0, intersection_Y = 0.0;
      int nRet;
      double l1x1 = (double) cX1;
      double l1y1 = (double) cY1;
      double l1x2 = (double) cX2;
      double l1y2 = (double) cY2;
      double l2x1 = (double) X1;
      double l2y1 = (double) Y1;
      double l2x2 = (double) X2;
      double l2y2 = (double) Y2;

    if( (Y1 >= cY1) && (Y2 >= cY1) ){
      //BACK
      *a = 0;
      *b = 0;
      *c = 0;
      *d = 0;
    }else if( (Y1 < cY1) && (Y2 < cY1) ){
      //FRONT
      *a = X2;
      *b = Y2;
      *c = 0;
      *d = 0;
    }else if( (Y1 > cY1) && (Y2 < cY1) ){
      //FIRST BACK --- SEC FRONT
      LineIntersection2(l1x1, l1y1, l1x2, l1y2,
                                  l2x1, l2y1, l2x2, l2y2,
                                 &intersection_X, &intersection_Y);
      *a = (int) round(intersection_X);
      *b = (int) round(intersection_Y);
      *c = X2;
      *d = Y2;
    }else if( (Y1 < cY1) && (Y2 >= cY1) ){
      //FIRST FRONT -- SEC BACK
      LineIntersection2(l1x1, l1y1, l1x2, l1y2,
                                  l2x1, l2y1, l2x2, l2y2,
                                 &intersection_X, &intersection_Y);
      *a = (int) round(intersection_X);
      *b = (int) round(intersection_Y);
      *c = 0;
      *d = 0;
    }


}

void isLeft(int cX1, int cX2, int cY1, int cY2,
                        int X1, int Y1, int X2,
                        int Y2, int *a, int *b,
                        int *c, int *d)
{

        double intersection_X = 0.0, intersection_Y = 0.0;
        int nRet;
        double l1x1 = (double) cX1;
        double l1y1 = (double) cY1;
        double l1x2 = (double) cX2;
        double l1y2 = (double) cY2;
        double l2x1 = (double) X1;
        double l2y1 = (double) Y1;
        double l2x2 = (double) X2;
        double l2y2 = (double) Y2;
      if( (X1 >= cX1) && (X2 >= cX1) ){
        //BACK
        *a = 0;
        *b = 0;
        *c = 0;
        *d = 0;
      }else if( (X1 < cX1) && (X2 < cX1) ){
        //FRONT
        *a = X2;
        *b = Y2;
        *c = 0;
        *d = 0;
      }else if( (X1 >= cX1) && (X2 < cX1) ){
        //FIRST BACK --- SEC FRONT
        LineIntersection2(l1x1, l1y1, l1x2, l1y2,
                                    l2x1, l2y1, l2x2, l2y2,
                                   &intersection_X, &intersection_Y);
        *a = (int) round(intersection_X);
        *b = (int) round(intersection_Y);
        *c = X2;
        *d = Y2;
      }else if( (X1 < cX1) && (X2 >= cX1) ){
        //FIRST FRONT -- SEC BACK
        LineIntersection2(l1x1, l1y1, l1x2, l1y2,
                                    l2x1, l2y1, l2x2, l2y2,
                                   &intersection_X, &intersection_Y);
        *a = (int) round(intersection_X);
        *b = (int) round(intersection_Y);
        *c = 0;
        *d = 0;
      }


}

void isUp(int cX1, int cX2, int cY1, int cY2,
                        int X1, int Y1, int X2,
                              int Y2, int *a, int *b,
                            int *c, int *d)
{

        double intersection_X = 0.0, intersection_Y = 0.0;
        int nRet;
        double l1x1 = (double) cX1;
        double l1y1 = (double) cY1;
        double l1x2 = (double) cX2;
        double l1y2 = (double) cY2;
        double l2x1 = (double) X1;
        double l2y1 = (double) Y1;
        double l2x2 = (double) X2;
        double l2y2 = (double) Y2;
      if( (Y1 >= cY1) && (Y2 >= cY1) ){
        //FRONT
        *a = X2;
        *b = Y2;
        *c = 0;
        *d = 0;
      }else if( (Y1 < cY1) && (Y2 < cY1) ){
        //BACK
        *a = 0;
        *b = 0;
        *c = 0;
        *d = 0;
      }else if( (Y1 >= cY1) && (Y2 < cY1) ){
        //FIRST BACK --- SEC FRONT
        LineIntersection2(l1x1, l1y1, l1x2, l1y2,
                                    l2x1, l2y1, l2x2, l2y2,
                                   &intersection_X, &intersection_Y);
        *a = (int) round(intersection_X);
        *b = (int) round(intersection_Y);
        *c = 0;
        *d = 0;
      }else if( (Y1 < cY1) && (Y2 >= cY1) ){
        //FIRST FRONT -- SEC BACK
        LineIntersection2(l1x1, l1y1, l1x2, l1y2,
                                    l2x1, l2y1, l2x2, l2y2,
                                   &intersection_X, &intersection_Y);
        *a = (int) round(intersection_X);
        *b = (int) round(intersection_Y);
        *c = X2;
        *d = Y2;
      }


}

void putTheElementsInArray(int *counterForArray,int *a,int *b,int *c,int *d)
{
  if( (*a == 0) && (*b == 0) && (*c == 0) && (*d == 0) )
  {
    (*counterForArray) -= 1;
  }
  else if( (*a != 0) && (*b != 0) && (*c == 0) && (*d == 0) )
  {
    array[ *counterForArray ][ 0 ] = *a;
    array[ *counterForArray ][ 1 ] = *b;
  }
  else
  {
    array[ *counterForArray ][ 0 ] = *a;
    array[ *counterForArray ][ 1 ] = *b;
    (*counterForArray) += 1;
    array[ *counterForArray ][ 0 ] = *c;
    array[ *counterForArray ][ 1 ] = *d;
  }
  *a = 0;
  *b = 0;
  *c = 0;
  *d = 0;
  (*counterForArray) +=1;
}

void createAllClippingPolygons()
{
      int cordX1, cordX2, cordY1, cordY2;
      int a = 0, b = 0, c = 0, d = 0;
      int counterForArray = 0;
      int size;

      //CREATE THE CLIPPING POLIGONS
      for( int i = 0; i < numberOfPolygons+1; i++)
      {
        counterForArray = 0;
        size = polygons[i].numOfPoints;
        memset(array, 0, 100);
        memset(array2, 0, 100);
        cordX1 = clippingArray[ 0 ].cord[ 0 ][ 0 ];
        cordY1 = clippingArray[ 0 ].cord[ 0 ][ 1 ];
        cordX2 = clippingArray[ 0 ].cord[ 1 ][ 0 ];
        cordY2 = clippingArray[ 0 ].cord[ 1 ][ 1 ];
        for( int l = 0; l < size ; l++)
        {
          if ( l == size-1 )
          {
            isRigth(cordX1, cordX2, cordY1, cordY2, polygons[i].arrayPoints[ l ].x,
                                                    polygons[i].arrayPoints[ l ].y,
                                                    polygons[i].arrayPoints[ 0 ].x,
                                                    polygons[i].arrayPoints[ 0 ].y,
                                                    &a, &b, &c, &d);
          }
          else
          {
            isRigth(cordX1, cordX2, cordY1, cordY2, polygons[i].arrayPoints[ l ].x,
                                                    polygons[i].arrayPoints[ l ].y,
                                                    polygons[i].arrayPoints[ l+1 ].x,
                                                    polygons[i].arrayPoints[ l+1 ].y,
                                                    &a, &b, &c, &d);
          }
          putTheElementsInArray(&counterForArray, &a, &b, &c, &d);

        }

        size = counterForArray ;
        memset(array2, 0, 100);
        memcpy(array2, array, sizeof(array));
        memset(array, 0, 100);
        counterForArray = 0;
        cordX1 = clippingArray[ 0 ].cord[ 1 ][ 0 ];
        cordY1 = clippingArray[ 0 ].cord[ 1 ][ 1 ];
        cordX2 = clippingArray[ 0 ].cord[ 2 ][ 0 ];
        cordY2 = clippingArray[ 0 ].cord[ 2 ][ 1 ];
        for( int l = 0; l < size ; l++)
        {
          if ( l == size-1 )
          {
            isDown(cordX1, cordX2, cordY1, cordY2, array2[ l ][ 0 ],
                                                   array2[ l ][ 1 ],
                                                   array2[ 0 ][ 0 ],
                                                   array2[ 0 ][ 1 ],
                                                   &a, &b, &c, &d);
          }
          else
          {
            isDown(cordX1, cordX2, cordY1, cordY2, array2[ l ][ 0 ],
                                                   array2[ l ][ 1 ],
                                                   array2[ l+1 ][ 0 ],
                                                   array2[ l+1 ][ 1 ],
                                                   &a, &b, &c, &d);
          }
          putTheElementsInArray(&counterForArray, &a, &b, &c, &d);

        }

        size = counterForArray;
        memset(array2, 0, 100);
        memcpy(array2, array, sizeof(array));
        memset(array, 0, 100);
        counterForArray = 0;
        cordX1 = clippingArray[ 0 ].cord[ 2 ][ 0 ];
        cordY1 = clippingArray[ 0 ].cord[ 2 ][ 1 ];
        cordX2 = clippingArray[ 0 ].cord[ 3 ][ 0 ];
        cordY2 = clippingArray[ 0 ].cord[ 3 ][ 1 ];
        for( int l = 0; l < size ; l++)
        {
          if ( l == size-1 )
          {
            isLeft(cordX1, cordX2, cordY1, cordY2, array2[ l ][ 0 ],
                                                   array2[ l ][ 1 ],
                                                   array2[ 0 ][ 0 ],
                                                   array2[ 0 ][ 1 ],
                                                   &a, &b, &c, &d);
          }
          else
          {
            isLeft(cordX1, cordX2, cordY1, cordY2, array2[ l ][ 0 ],
                                                   array2[ l ][ 1 ],
                                                   array2[ l+1 ][ 0 ],
                                                   array2[ l+1 ][ 1 ],
                                                   &a, &b, &c, &d);
          }
          putTheElementsInArray(&counterForArray, &a, &b, &c, &d);

        }

        size = counterForArray;
        memset(array2, 0, 100);
        memcpy(array2, array, sizeof(array));
        memset(array, 0, 100);
        counterForArray = 0;
        cordX1 = clippingArray[ 0 ].cord[ 3 ][ 0 ];
        cordY1 = clippingArray[ 0 ].cord[ 3 ][ 1 ];
        cordX2 = clippingArray[ 0 ].cord[ 0 ][ 0 ];
        cordY2 = clippingArray[ 0 ].cord[ 0 ][ 1 ];
        for( int l = 0; l < size ; l++)
        {
          if ( l == size-1 )
          {
            isUp(cordX1, cordX2, cordY1, cordY2, array2[ l ][ 0 ],
                                                 array2[ l ][ 1 ],
                                                 array2[ 0 ][ 0 ],
                                                 array2[ 0 ][ 1 ],
                                                 &a, &b, &c, &d);
          }
          else
          {
            isUp(cordX1, cordX2, cordY1, cordY2, array2[ l ][ 0 ],
                                                 array2[ l ][ 1 ],
                                                 array2[ l+1 ][ 0 ],
                                                 array2[ l+1 ][ 1 ],
                                                 &a, &b, &c, &d);
          }
          putTheElementsInArray(&counterForArray, &a, &b, &c, &d);

        }

        for( int k = 0; k < counterForArray; k++)
        {
          clippingArray[ i ].arrayPoints[ k ].x = array[ k ][ 0 ];
          clippingArray[ i ].arrayPoints[ k ].y = array[ k ][ 1 ];
        }

        takeTheTrianglePointsForClippingArray(counterForArray, i);
        clippingArray[ i ].numOfPoints = counterForArray;
        clippingArray[ i ].colorFillArray[0] = polygons[ i ].colorFillArray[0];
        clippingArray[ i ].colorFillArray[1] = polygons[ i ].colorFillArray[1];
        clippingArray[ i ].colorFillArray[2] = polygons[ i ].colorFillArray[2];

        clippingArray[ i ].colorLineArray[0] = polygons[ i ].colorLineArray[0];
        clippingArray[ i ].colorLineArray[1] = polygons[ i ].colorLineArray[1];
        clippingArray[ i ].colorLineArray[2] = polygons[ i ].colorLineArray[2];
      }

}

void displayClipingPolygonPoints(int t)
{
  glColor3f(0.00, 0.00, 0.00);
  glPointSize(2.0f);
  glBegin(GL_POINTS);
  for( int k = 0; k < clippingArray[ t ].numOfPoints; k++ )
  {
    glVertex3f(clippingArray[ t ].arrayPoints[ k ].x,
               clippingArray[ t ].arrayPoints[ k ].y , 0);
  }

  glEnd();
}

void displayClipingPolygonLines(int t)
{
  glLineWidth(2);
  glColor3f(clippingArray[ t ].colorLineArray[0],
            clippingArray[ t ].colorLineArray[1],
            clippingArray[ t ].colorLineArray[2]);

  glBegin(GL_LINES);
  //draw line to this points
  for(int k = 0; k < clippingArray[ t ].numOfPoints-1; k++ )
  {
     glVertex3f(clippingArray[ t ].arrayPoints[ k ].x ,
                clippingArray[ t ].arrayPoints[ k ].y , 0);

     glVertex3f(clippingArray[ t ].arrayPoints[ k+1 ].x,
                clippingArray[ t ].arrayPoints[ k+1 ].y, 0);
  }
  glVertex3f(clippingArray[ t ].arrayPoints[ clippingArray[ t ].numOfPoints-1 ].x,
             clippingArray[ t ].arrayPoints[ clippingArray[ t ].numOfPoints-1 ].y , 0);

  glVertex3f(clippingArray[ t ].arrayPoints[ 0 ].x,
             clippingArray[ t ].arrayPoints[ 0 ].y, 0);

  glEnd();
}

void displayClipingPolygonNames(int t)
{
  char letters[1];
  strcpy(letters,"A");
  int len=strlen(letters);
  glColor3f(0,0,0);
  glMatrixMode( GL_MODELVIEW );
  glPushMatrix();
  glLoadIdentity();
  for(int k = 0; k < clippingArray[ t ].numOfPoints; k++){
    glRasterPos2i(clippingArray[ t ].arrayPoints[ k ].x -5 ,
                  clippingArray[ t ].arrayPoints[ k ].y +10 );

    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, letters[0]);
    letters[0]++;
  }
}

void displayClipingPolygonTriangulate(int t)
{
  glLineWidth(1);
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINES);
	for( l = 0; l < clippingArray[t].pointsForTriangle - 1; l+=3 )
	{
			glVertex3f(clippingArray[t].arrayTrianglePoints[l].x, clippingArray[t].arrayTrianglePoints[l].y, 0);
			glVertex3f(clippingArray[t].arrayTrianglePoints[l+1].x, clippingArray[t].arrayTrianglePoints[l+1].y, 0);
			glVertex3f(clippingArray[t].arrayTrianglePoints[l].x, clippingArray[t].arrayTrianglePoints[l].y, 0);
			glVertex3f(clippingArray[t].arrayTrianglePoints[l+2].x, clippingArray[t].arrayTrianglePoints[l+2].y, 0);
			glVertex3f(clippingArray[t].arrayTrianglePoints[l+1].x, clippingArray[t].arrayTrianglePoints[l+1].y, 0);
			glVertex3f(clippingArray[t].arrayTrianglePoints[l+2].x, clippingArray[t].arrayTrianglePoints[l+2].y, 0);
	}
	glEnd();
}

void paintClipingPolygon(int t)
{
  glColor3f(clippingArray[ t ].colorFillArray[0],
            clippingArray[ t ].colorFillArray[1],
            clippingArray[ t ].colorFillArray[2]);


  printf("\n\n Mpika");
  for(int k = 0; k < clippingArray[t].pointsForTriangle - 1; k+=3 )
  {
      glBegin(GL_POLYGON);
    printf("\n\n pointsforTriangle %d\n\n",clippingArray[t].pointsForTriangle - 1);
     glVertex3f(clippingArray[t].arrayTrianglePoints[k].x, clippingArray[t].arrayTrianglePoints[k].y, 0 );
     glVertex3f(clippingArray[t].arrayTrianglePoints[k+1].x, clippingArray[t].arrayTrianglePoints[k+1].y, 0 );

     glVertex3f(clippingArray[t].arrayTrianglePoints[k+1].x, clippingArray[t].arrayTrianglePoints[k+1].y, 0 );
     glVertex3f(clippingArray[t].arrayTrianglePoints[k+2].x, clippingArray[t].arrayTrianglePoints[k+2].y, 0 );

     glVertex3f(clippingArray[t].arrayTrianglePoints[k+2].x, clippingArray[t].arrayTrianglePoints[k+2].y, 0 );
     glVertex3f(clippingArray[t].arrayTrianglePoints[k].x, clippingArray[t].arrayTrianglePoints[k].y, 0 );
     glEnd();
  }

}

void displayClipingPolygons()
{

  //DISPLAY THE CLIPPING POLYGONS
  for( int t = 0; t < numberOfPolygons+1; t++)
  {
    //IF T KEY PRESSED ---- 0 = FALSE --- 1 = TRUE ---
    if( showPolygonsAsTriangles == 0)
    {
      displayClipingPolygonPoints(t);
      displayClipingPolygonLines(t);
      displayClipingPolygonNames(t);
      paintClipingPolygon(t);
    }
    else
    {
      paintClipingPolygon(t);
      displayClipingPolygonTriangulate(t);

    }

  }
}

void display()
{
    glutSwapBuffers();
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glMatrixMode(GL_MODELVIEW);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 600, 0.0, 500);
	if (extrudeBtn == 1 )
	{
		expandTheTriangles();

	}
	else
	{
	   // CLIPING BUTTON PRESSED --- TOOK ALL
	  if( clippingBtn == 1 && clippingCord == 2 )
	  {
	    createClippingPolygon();
	    displayClipingPolygons();
	  }
	  else
	  {
	    createPolygon();
	  }
	}

  glMatrixMode( GL_MODELVIEW );
  glPushMatrix();
  glLoadIdentity();
  //it needs this to display the polygon
  glPopMatrix();
  glMatrixMode( GL_PROJECTION );
  glPopMatrix();
  glMatrixMode( GL_MODELVIEW );
  glFlush();
}

void keyboard(unsigned char key, int x, int y)
{
	//CHECK FOR "T" and "t"
	if(int(key) == 84 || int(key) == 116)
	{
		counterForT++;
		if(counterForT % 2 == 1)
		{
			showPolygonsAsTriangles = 1;
		}
		else
		{
			showPolygonsAsTriangles = 0;
		}
		glutPostRedisplay();
	}
}

void initialiazeAllTheFillColors()
{
  for(int i = 0; i < 20; i++)
  {
    polygons[ i ].colorFillArray[0] = 1.0;
    polygons[ i ].colorFillArray[1] = 1.0;
    polygons[ i ].colorFillArray[2] = 1.0;
    clippingArray[ i ].colorFillArray[0] = 1.0;
    clippingArray[ i ].colorFillArray[1] = 1.0;
    clippingArray[ i ].colorFillArray[2] = 1.0;
  }
}


int main(int argc , char ** argv)
{
  initialiazeAllTheFillColors();


   // Initialize glut
   glutInit(&argc, argv);
     // Create the window
     glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB );
     glutInitWindowPosition(100,100);
     glutInitWindowSize(600,500);
     glutCreateWindow("Project 1");
     glutKeyboardFunc(keyboard);
     //Unfixed size

     createMenu();

     // Set the display function
     glutDisplayFunc(display);
     glutReshapeFunc(resize);
     glutIdleFunc(display);


     glutSpecialFunc(processSpecialKeys);

     glEnable(GL_DEPTH_TEST);

   // Active Main

	glutMainLoop();

	return 0 ;
}
