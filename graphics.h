/*
	This library is provided as is and the Author doesnot share any accountability nor guarentee any.
	#ppvftw
	contact me at pratapppv@gmail.com
*/
#pragma once
#ifndef GRAPHICS_H
#define GRAPHICS_H
#define FOREGROUND_REDLIGHT 0x000C 

#include <iostream>
#include <math.h>
#include <windows.h>
#include <Windows.h>
#include <windef.h>
#include <string>

using namespace std;

/*
#define BLACK "0"
#define BLUE "1"
#define GREEN "2"
#define CYAN "3"
#define RED "4"
#define PURPLE "5"
#define YELLOW "6"
#define WHITE "7"
#define GREY "8"
#define LIGHTBLUE "9"
#define LIGHTGREEN "A"
#define LIGHTCYAN "B"
#define LIGHTRED "C"
#define LIGHTPURPLE "D"
#define LIGHTYELLOW "E"

string bg = to_string(RGB(0, 0, 0));
string fc = to_string(RGB(0, 0, 0));
*/

struct rgb
{
	int r;
	int g;
	int b;
};

static class canvas
{
protected:
	COORD BGN, POS;
	short mov;
	short movx;
	HWND hWnd;
	RECT pRECT;
	COORD POS1;
	COORD BGN1;
	HDC hDC;
	HANDLE StdOut;
	COORD setCordScale(COORD, RECT);

public:

	canvas()
	{
		mov = 30;
		movx = 0;
		hWnd = GetForegroundWindow();
		pRECT = { 0 };
		POS1 = { 0 };
		BGN1 = setCordScale(POS1, pRECT);
		GetWindowRect(hWnd, &pRECT);
		hDC = GetWindowDC(hWnd);
		StdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	}
	HPEN getPen(int iPEN_STYLE, int iPEN_SIZE, int iCOLORREF)
	{
		return CreatePen(iPEN_STYLE, iPEN_SIZE, iCOLORREF);
	}
};

COORD canvas::setCordScale(COORD POS, RECT pRECT)
{
	if (POS.X == 0)
		POS.X = 1;
	if (POS.Y == 0)
		POS.Y = 1;

	int nROWS = 25;
	int nCOLS = 80;

	double CX = (pRECT.right - pRECT.left) / nCOLS;
	double CY = (pRECT.bottom - pRECT.top) / nROWS;


	POS.X *= CX;
	POS.Y *= CY;

	int xBORDER = GetSystemMetrics(SM_CXBORDER);
	int yBORDER = GetSystemMetrics(SM_CYMENU);
	int xDRAG = GetSystemMetrics(SM_CXDRAG);
	int yDRAG = GetSystemMetrics(SM_CYDRAG);

	POS.X += xBORDER + xDRAG;
	POS.Y += yBORDER + yDRAG;
	return POS;
}


class rect :public canvas
{
	HPEN PEN;
	int thick;
	BOOL PlotRect(HDC, HPEN, int r, int g, int b);

public:
	void draw(int x1, int y1, int x2, int y2, int r, int g, int b);
	rect(int thik,int r,int g,int b)
	{
		thick = thik;
		PEN = getPen(PS_SOLID, thik, RGB(r,g,b));
	}
	void Delete();
};

/*
x1 and y1 are the corrdinates of the top left hand vertex
x2 and y2 are the corrdinates of the bottom right hand vertex
r,g,b are the values to fill the rectangle
*/

void rect::draw(int x1, int y1, int x2, int y2, int r, int g, int b)
{
	BGN.X = (short)x1 + movx;
	BGN.Y = (short)y1 + mov;
	POS.X = (short)x2 + movx;
	POS.Y = (short)y2 + mov;
	PlotRect(hDC, PEN,r,g,b);
	
}

BOOL rect::PlotRect(HDC hDC, HPEN hPen, int r,int g,int b)
{
	SelectObject(hDC, hPen);
	RECT a;
	a.bottom = POS.Y - thick+1;
	a.right = POS.X - thick+1;
	a.top = BGN.Y + thick-2;
	a.left = BGN.X + thick-2;
	Rectangle(hDC, BGN.X, BGN.Y, POS.X, POS.Y);
	HBRUSH brush = CreateSolidBrush(RGB(r, g, b));
	FillRect(hDC, &a, brush);
	DeleteObject(brush);
	return true;
}

void rect::Delete()
{
	if (bg == "0")
		PEN = getPen(PS_SOLID, thick, RGB(0, 0, 0));
	else if (bg == "1")
		PEN = getPen(PS_SOLID, thick, RGB(0,0,128));
	SelectObject(hDC, PEN);
	RECT a;
	a.bottom = POS.Y;
	a.right = POS.X;
	a.top = BGN.Y;
	a.left = BGN.X;
	Rectangle(hDC, BGN.X, BGN.Y, POS.X, POS.Y);
	HBRUSH brush;
	if (bg == "0")
		brush = CreateSolidBrush(RGB(0, 0, 128));
	else if (bg == "1")
		 brush = CreateSolidBrush(RGB(0, 0, 128));
	else
		brush = CreateSolidBrush(RGB(0, 0, 0));
	FillRect(hDC, &a, brush);
	DeleteObject(brush);
	DeleteObject(PEN);
}

class line :public canvas
{
	HPEN PEN;
	int thick;
	BOOL PlotLine();
public:
	void draw(int x1, int y1, int x2, int y2);
	void Delete();
	line(int thic, int r, int g, int b)
	{
		thick = thic;
		PEN = getPen(PS_SOLID, thic, RGB(r, g, b));
	}
};

/*
	x1 and y1 are the coordinates of the start of the line
	x2 and y2 are the coordinates of the end of the line
*/

void line::Delete()
{
	PEN = getPen(PS_SOLID, thick, RGB(0, 0, 0));
	SelectObject(hDC, PEN);
	MoveToEx(hDC, BGN.X, BGN.Y, NULL);
	LineTo(hDC, POS.X, POS.Y);
	DeleteObject(PEN);
}

void line::draw(int x1, int y1, int x2, int y2)
{
		BGN.X = (short)x1 + movx;
		BGN.Y = (short)y1 + mov;
		POS.X = (short)x2 + movx;
		POS.Y = (short)y2 + mov;
		PlotLine();
}

BOOL line::PlotLine()
{
		SelectObject(hDC, PEN);
		MoveToEx(hDC, BGN.X, BGN.Y, NULL);
		LineTo(hDC, POS.X, POS.Y);
		return true;
}


class circle:public canvas
{
	HPEN PEN;
	int thick;
	BOOL PlotCirc(int r,int g,int b);
public:
	void Delete();
	void draw(int x, int y, int rad,int r,int g,int b);
	circle(int thic, int r, int g, int b)
	{
		thick = thic;
		PEN = getPen(PS_SOLID, thic, RGB(r, g, b));
	}
};

void circle::Delete()
{
	PEN = getPen(PS_SOLID, thick, RGB(0, 0, 0));
	SelectObject(hDC, PEN);
	HBRUSH hbr = CreateSolidBrush(RGB(0, 0, 0));
	HBRUSH hOld = (HBRUSH)SelectObject(hDC, hbr);
	Ellipse(hDC, BGN.X, BGN.Y, POS.X, POS.Y);
	DeleteObject(hbr);
	DeleteObject(hOld);
	DeleteObject(PEN);
}

void circle::draw(int x, int y, int rad, int r, int g, int b)
{
	BGN.X = (short)x + movx - rad / 2;
	BGN.Y = (short)y + mov - rad / 2;
	POS.X = (short)x + movx + rad / 2;
	POS.Y = (short)y + mov + rad / 2;
	PlotCirc(r,g,b);
}

BOOL circle::PlotCirc(int r,int g,int b)
{
	SelectObject(hDC, PEN);
	HBRUSH hbr = CreateSolidBrush(RGB(r, g, b));
	HBRUSH hOld = (HBRUSH)SelectObject(hDC, hbr);
	Ellipse(hDC, BGN.X, BGN.Y, POS.X, POS.Y);
	DeleteObject(hbr);
	DeleteObject(hOld);
	DeleteObject(PEN);
	return true;
}

struct mouse
{
	long x;
	long y;
};

class Mouse:protected canvas
{
protected:
	int keyPressed(int key)
	{
		return (GetAsyncKeyState(key));
	}
public:
	mouse FSmouse()
	{
		POINT a;
		GetCursorPos(&a);
		mouse p;
		p.x = a.x;
		p.y = a.y;
		return p;
	}

	mouse Smouse()
	{
		POINT a;
		GetCursorPos(&a);
		ScreenToClient(hWnd, &a);
		mouse p;
		p.x = a.x;
		p.y = a.y;
		return p;

	}

	char getMouseClick()
	{
		if (keyPressed(VK_LBUTTON) == -32768)
		{
			return 'L';
		}
		else if (keyPressed(VK_RBUTTON))
		{
			return 'R';
		}
	}

};


int getmaxx(void) { return 640; }
int getmaxy(void) { return 300; }

/*
class font :protected canvas
{
	PAINTSTRUCT ps;
	HFONT hFont;
	HDC hdc;
public:
	void cfont(string);
	font()
	{
		 hdc = BeginPaint(hWnd, &ps);
	}

};

void font::cfont(string f)
{
}
*/

void clear_text()
{
	system("cls");
}
rgb getPixel(int x, int y)
{
	rgb clr;
	HDC dc = GetDC(NULL);
	COLORREF color = GetPixel(dc, x, y);
	ReleaseDC(NULL, dc);
	clr.r = GetRValue(color);
	clr.g = GetGValue(color);
	clr.b = GetBValue(color);
	return clr;
}
#endif