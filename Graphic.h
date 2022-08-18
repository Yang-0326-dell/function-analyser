#pragma once
#ifndef GRAPHIC_H
#define GRAPHIC_H

#include "Header.h"
class Graphic
{
public:
	COLORREF ac = RGB(255, 255, 255);
	COLORREF color = RGB(255, 255, 0);
	COLORREF lc = RGB(0, 0, 180);
	HWND hWnd = GetConsoleWindow();
	HDC hdc = GetDC(hWnd);
	double height=0;
	double width=0;
	double radio = 1;
	fs f;
	fs O;
	long double precision;
	vector<int> num;
	Graphic();
	bool ini();
	bool draw_axis();
	bool draw_fun(double,long double);
	bool redraw();
};

#endif