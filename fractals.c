// includes
#include "gfx.h"
#include <stdbool.h>
#include <unistd.h>
#include <math.h>
#include <stdio.h>

// function prototypes
void sierpinski(int x1, int y1, int x2, int y2, int x3, int y3);
void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3);
void shrinking(int x, int y, int len);
void drawSquare(int x, int y, int len);
void spiral_squares(int x, int y, float len, float rad, int ang);
void circular(int x, int y, int len);
void snowflake(int x, int y, int len);
void tree(int x, int y, float len, int ang);
void fern(int x, int y, float len, int ang);
void spiral(int x, int y, float ang);

int main() {
	int width = 700, height = 700, mrgn = 20;
  	bool loop = true;
	int x = 350, y = 350, len = 200;
	char c;

  	gfx_open(width, height, "Fractal Puzzles");

  	while (loop) {
    	c = gfx_wait();
    	gfx_clear();
    	switch (c) {
      	case '1': // Sierpinski Triangle   
        	// set up some variables
        	sierpinski(mrgn, mrgn, width-mrgn, mrgn, width/2, height-mrgn); // call of recursive funtion
        	break;
      	case '2': // Shrinking Squares 
			shrinking(x, y, len); 
        	break;
		case '3': // Spiral Squares
			spiral_squares(x, y, 1, 1, 0);
			break;
		case '4': // Circular lace
			circular(x, y, len);
			break;
		case '5': // Snowflake
			snowflake(x, y, len);
			break;
		case '6': // Tree
			gfx_line(x, y+250, x, y);
			tree(x, y, 115, 180);
			break;
		case '7': // Fern
			fern(x, y+250, 100, 90);
			break;
      	case '8': // Spiral of Spirals
			spiral(x, y, 12*M_PI); 
        	break;
      	case 'q':
        	loop = false;
      	default:
        	break;
    	}	
	}

  return 0;
}

// all functions go here

void sierpinski(int x1, int y1, int x2, int y2, int x3, int y3)
{
  // Draw a triangle
  drawTriangle(x1, y1, x2, y2, x3, y3);

  gfx_flush();

  // Base case
  if(abs(x2-x1) < 5) return;

  // Recursive calls
  sierpinski(x1, y1, (x1+x2)/2, (y1+y2)/2, (x1+x3)/2, (y1+y3)/2);
  sierpinski((x1+x2)/2, (y1+y2)/2, x2, y2, (x2+x3)/2, (y2+y3)/2);
  sierpinski((x1+x3)/2, (y1+y3)/2, (x2+x3)/2, (y2+y3)/2, x3, y3);
}

void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3)
{
  gfx_line(x1,y1,x2,y2);
  gfx_line(x2,y2,x3,y3);
  gfx_line(x3,y3,x1,y1);
}

void shrinking(int x, int y, int len) 
{ 
	// draw a square
	drawSquare(x, y, len/2);

	len = len/2;

	gfx_flush();

	// base case
	if(abs(len) < 3) return;
     
	// recursive calls
	shrinking(x - len, y - len, len);
	shrinking(x - len, y + len, len);
	shrinking(x + len, y + len, len);
	shrinking(x + len, y - len, len);
}

void drawSquare(int x, int y, int len) 
{
  gfx_line(x - len/2, y + len/2, x - len/2, y - len/2);
  gfx_line(x - len/2, y - len/2, x + len/2, y - len/2);
  gfx_line(x + len/2, y + len/2, x + len/2, y - len/2);
  gfx_line(x - len/2, y + len/2, x + len/2, y + len/2);
}

void spiral_squares(int x, int y, float len, float rad, int ang) 
{
	int x1 = x + rad*cos(ang*M_PI/180);
	int y1 = y + rad*sin(ang*M_PI/180);

	// draw a square
	drawSquare(x1, y1, len);

	gfx_flush();

	// base case
	if (len > 150) return;

	// recursive call
	spiral_squares(x, y, 1.09*len, 1.12*rad, ang-36); 
}

void circular(int x, int y, int len)
{
	// draw a circle
	gfx_circle(x, y, len);

	gfx_flush();

	// base case
	if(abs(len) < 1) return;
	int i;
	int newX;
	int newY;
	for (i = 0; i < 6; i++) {
		newX = x + len*cos(M_PI*i/3); // draws 6 circles
		newY = y + len*sin(M_PI*i/3);
		circular(newX, newY, len/3); // recursive call
	}
}

void snowflake(int x, int y, int len)
{	
	gfx_flush();
	
	// base case
	if(abs(len) < 1) return;

	int i;
	int newX;
	int newY;
	for (i = 0; i < 5; i++) {
		newX = x + len*cos(72*i*M_PI/180);
		newY = y + len*sin(72*i*M_PI/180);
		gfx_line(x, y, newX, newY); // draws line
		snowflake(newX, newY, len/4); // recursive call
	}
}

void tree(int x, int y, float len, int ang) 
{
	gfx_flush();
	
	// base case
	if(len < 1) return;

	// right side
	int i;
	int newXr;
	int newYr;
	for (i = 1; i < 2; i++) {
		newXr = x + len*cos(ang*M_PI/180+M_PI/3); // node has 5 branches
		newYr = y + len*sin(ang*M_PI/180+M_PI/3);
		gfx_line(x, y, newXr, newYr); // draws line
		tree(newXr, newYr, len*2/3, ang-36); // recursive call
	}
	// left side
	int j;
	int newXl;
	int newYl;
	for (j = 1; j < 2; j++) {
		newXl = x + len*cos(ang*M_PI/180+2*M_PI/3);
		newYl = y + len*sin(ang*M_PI/180+2*M_PI/3);
		gfx_line(x, y, newXl, newYl); // draws line
		tree(newXl, newYl, len*2/3, ang+36); // recursive call
	}
}

void fern(int x, int y, float len, int ang) 
{
	int x2 = x + len*cos(ang*M_PI/180);
	int y2 = y - len*sin(ang*M_PI/180);

	gfx_flush();

	// base case
	if (len < 1) return;

	int i;
	for(i = 0; i < 4; i++) { // total of 8 recursive calls
		gfx_line(x, y, x2, y2); // draws line
		fern(x2, y2, len/3, ang+30); // 2 recursive calls
		fern(x2, y2, len/3, ang-30);
		x2 = x2 + len*cos(ang*M_PI/180); // recalculate coordinates to draw next line
		y2 = y2 - len*sin(ang*M_PI/180);
	}
}

void spiral(int x, int y, float ang) 
{
	float i;
	for (i = ang; i > 0; i = i - M_PI/7) {
		float r = exp(i/5.5); // radius
		if (r < 3) return; // base case
		float x1 = x + r*cos(i);
		float y1 = y - r*sin(i);
		gfx_point(x1, y1); // draws point
		spiral(x1, y1, i - 2*M_PI); // decrease angle for each recursive call
	}
}








