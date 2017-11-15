// NGRAPHICS.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "graphics.h"
#include <conio.h>
using namespace std;

void main()
{
	rect r(4, 0, 255, 0); // the first argument tells the thickness and the remaining 3 tell the RGB values of the colour of the outline of the rect
	r.draw(20, 10, 100, 100,0,0,255); // check comments of the graphics.h file to understand 
	_getch();
	r.Delete(); // deletes the rectangle. dosent delete the object. for that make it a pointer and use the delete command. ask Vasudha maam bout that
	_getch();

	line n(2, 0, 0, 255);// the first argument tells the thickness and the remaining 3 tell the RGB values of the colour of the outline of the line
	n.draw(20, 10, 100, 100); // check comments of the graphics.h file to understand
	_getch();
	n.Delete();
	_getch();

	circle c(2, 0, 255, 0);
	c.draw(200, 100, 100, 0, 0, 255); //you guys can figure this out
	_getch();
	c.Delete();
	_getch();

	//so heres how u use the mouse functions(PS ignore the grammer and the spellings and the variable names. its 1130 in the night and i dont have coffee)

	Mouse m;
	m.FSmouse();
	m.getMouseClick();
	m.Smouse();

	// so thats all there is for today. Ill add some more stuff tomm like polygons and text stuff. but for now sayonara GN SD

	// also for getmaxx and getmaxy this is what u do

	getmaxx();
	getmaxy();
}

