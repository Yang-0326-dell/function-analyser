#ifndef GRAPHIC_CPP
#define GRAPHIC_CPP

#include "Graphic.h"
#include "control.cpp"

Graphic::Graphic() {
	HWND hWnd = GetConsoleWindow();
	HDC hdc = GetDC(hWnd);
}

bool Graphic::ini() {
	f = SetSize();
	O.X = f.X / 2+100;
	O.Y = f.Y / 2+100;
	width = CONTROL_CPP::input_flo("Width=", 0, 1000, 2);
	height = CONTROL_CPP::input_flo("Height=", width * 0.5, width * 2, 2);

	//precision = CONTROL_CPP::input_flo("precision:(Note: if you input 0.1, then the image will be at intervals of 0.1)", width / 5000.0, (width) / 10.0, 1);
	radio = double(f.X) /width;
	precision = 1.000 / radio;
	system("cls");
	return false;
}
bool Graphic::draw_axis() {
	for (int x = O.X - width / 2 * radio; x < O.X + width / 2 * radio; x++) {
		SetPixel(hdc, x + 100, O.Y - width / 2 * radio, lc);
		SetPixel(hdc, x + 100, O.Y - width / 10 * 4 * radio, lc);
		SetPixel(hdc, x + 100, O.Y - width / 10 * 3 * radio, lc);
		SetPixel(hdc, x + 100, O.Y - width / 10 * 2 * radio, lc);
		SetPixel(hdc, x + 100, O.Y - width / 10 * radio, lc);
		SetPixel(hdc, x + 100, O.Y, ac);
		SetPixel(hdc, x + 100, O.Y + width / 10 * radio, lc);
		SetPixel(hdc, x + 100, O.Y + width / 10 * 2 * radio, lc);
		SetPixel(hdc, x + 100, O.Y + width / 10 * 3 * radio, lc);
		SetPixel(hdc, x + 100, O.Y + width / 10 * 4 * radio, lc);
		SetPixel(hdc, x + 100, O.Y + width / 2 * radio, lc);
	}
	for (int y = O.Y - width / 2 * radio; y<O.Y + width / 2 * radio; y++) {
		SetPixel(hdc, O.X - width / 2 * radio, y + 100, lc);
		SetPixel(hdc, O.X - width / 10 * 4 * radio, y + 100, lc);
		SetPixel(hdc, O.X - width / 10 * 3 * radio, y + 100, lc);
		SetPixel(hdc, O.X - width / 10 * 2 * radio, y + 100, lc);
		SetPixel(hdc, O.X - width / 10 * radio, y + 100, lc);
		SetPixel(hdc, O.X, y + 100, ac);
		SetPixel(hdc, O.X + width / 10 * radio, y + 100, lc);
		SetPixel(hdc, O.X + width / 10 * 2 * radio, y + 100, lc);
		SetPixel(hdc, O.X + width / 10 * 3 * radio, y + 100, lc);
		SetPixel(hdc, O.X + width / 10 * 4 * radio, y + 100, lc);
		SetPixel(hdc, O.X + width / 2 * radio, y + 100, lc);
	}
	for (int i = 0; i < ARROW; i++) {
		SetPixel(hdc, O.X + width / 2*radio - i+100, O.Y + i, ac);
		SetPixel(hdc, O.X + width / 2 * radio - i+100, O.Y - i, ac);
		SetPixel(hdc, O.X - i, O.Y - width / 2 * radio+i+100, ac);
		SetPixel(hdc, O.X + i, O.Y - width / 2 * radio + i+100, ac);

	}
	int r = 10;
	for (int x = -r / 2; x < r / 2; x++) {
		for (int y = -r / 2; y < r / 2; y++) {
			if (x * x + y *y < r * r/4) {
				SetPixel(hdc, O.X + x, O.Y - y, ac); 
				SetPixel(hdc, O.X + x, O.Y - y-width/10.0*radio, RGB(255,0,0));
			}
		}
	}

	cout << "the red dot is at (0," << width / 10 << ")" << endl;
	return false;
}

bool Graphic::draw_fun(double x,long double y) {
	if (y == INFINITY||y>f.Y/radio) {
		y = long double(f.Y / radio);
	}
	else if (y == -INFINITY||y< -f.Y / radio) {
		y = (long double)-f.Y / radio;
	}
		int num_size = num.size();
		SetPixel(hdc, x * radio + O.X, O.Y - y * radio, color);
		num.push_back(y * radio);
		if (num_size > 1) {
			if (num[num_size - 2] > y * radio) {
				for (int m = 0; m <= (num[num_size - 2] - y * radio) / 2; m++) {
					SetPixel(hdc, x * radio + O.X - 1, O.Y - ((num[num_size - 2] + y * radio) / 2 - m), color);
					SetPixel(hdc, x * radio + O.X, O.Y - ((num[num_size - 2] + y * radio) / 2 + m), color);
				}
			}
			else if (num[num_size - 2] < y * radio) {
				for (int m = 0; m <= -(num[num_size - 2] - y * radio) / 2; m++) {
					SetPixel(hdc, x * radio + O.X - 1, O.Y - ((num[num_size - 2] + y * radio) / 2 + m), color);
					SetPixel(hdc, x * radio + O.X, O.Y - ((num[num_size - 2] + y * radio) / 2 - m), color);
				}
			}
		}
	return 1;
}

bool Graphic::redraw() {
	for (int i = 0; i < num.size(); i++) {
		SetPixel(hdc, (i - width / 2) * radio + O.X, O.Y - num[i] * radio, color);
	}
	return 1;
}

#endif