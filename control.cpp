#ifndef CONTROL_CPP
#define CONTROL_CPP

#include "Header.h"

bool inline input_num(string req, int* r) {
	string m = "";
_1:
	cout << req;
	cin >> m;
	try {
		*r = stoi(m);
	}
	catch (...) {
		cout << "Not valid! Please try again." << endl;
		goto _1;
	}
	return false;
}
bool inline input_num(string req, bool* r) {
	string m = "";
	int rd = 0;
_1:
	cout << req;
	cin >> m;
	try {
		rd = stoi(m);
	}
	catch (...) {
		cout << "Not valid! Please try again." << endl;
		goto _1;
	}
	*r = rd;
	return false;
}
bool inline input_num(string req, long double* r) {
	string m = "";
_1:
	cout << req;
	cin >> m;
	try {
		*r = stoi(m);
	}
	catch (...) {
		cout << "Not valid! Please try again." << endl;
		goto _1;
	}
	return false;
}

int inline input_num(string req, long double r1, long double r2, short mode) {
	string m = "";
	long double r = 0;
_1:
	cout << req;
	cin >> m;
	try {
		r = stoi(m);
	}
	catch (...) {
		cout << "Not valid! Please try again." << endl;
		goto _1;
	}
	if (r >= r1 && r <= r2) {
		if (mode == 1) {
			return 1 / r;
		}
		else if (mode == 2) {
			return r;
		}
	}
	else {
		cout << "too small or too big! Please input somthing bigger than" << r1 << " and smaller than" << r2 << endl;
		goto _1;
	}

}

long double inline input_flo(string req, long double r1, long double r2,int mode) {
	string m = "";
	long double r = 0;
_1_:
	cout << req;
	cin >> m;
	try {
		r = stof(m);
	}
	catch (...) {
		cout << "Not valid! Please try again." << endl;
		goto _1_;
	}
	if (r >= r1 && r <= r2) {
		return r;
	}
	else {
		cout << "too small or too big! Please input somthing bigger than" << r1 << " and smaller than" << r2 << endl;
		goto _1_;
	}
	return false;
}


inline COORD get_font_size() {
	COORD font_size;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	struct CONSOLE_FONT
	{
		DWORD index;
		COORD dim;
	} cfi;
	typedef COORD(WINAPI* PROCGETCONSOLEFONTSIZE)(HANDLE, DWORD);
	typedef BOOL(WINAPI* PROCGETCURRENTCONSOLEFONT)(HANDLE, BOOL, struct CONSOLE_FONT*);

	HMODULE hKernel32 = GetModuleHandle(L"kernel32");
	PROCGETCONSOLEFONTSIZE GetConsoleFontSize = (PROCGETCONSOLEFONTSIZE)GetProcAddress(hKernel32, "GetConsoleFontSize");
	PROCGETCURRENTCONSOLEFONT GetCurrentConsoleFont = (PROCGETCURRENTCONSOLEFONT)GetProcAddress(hKernel32, "GetCurrentConsoleFont");

	GetCurrentConsoleFont(handle, FALSE, &cfi);
	font_size = GetConsoleFontSize(handle, cfi.index);

	return font_size;
}


inline VOID KillConsoleCloseButton(VOID) {
	HWND hWnd = GetConsoleWindow();
	HDC hdc = GetDC(hWnd);
	DeleteMenu(GetSystemMenu(GetConsoleWindow(), FALSE), SC_CLOSE, MF_DISABLED);
	DeleteMenu(GetSystemMenu(GetConsoleWindow(), FALSE), SC_MAXIMIZE, MF_DISABLED);
	DeleteMenu(GetSystemMenu(GetConsoleWindow(), FALSE), SC_MINIMIZE, MF_DISABLED);
	DeleteMenu(GetSystemMenu(GetConsoleWindow(), FALSE), SC_MOUSEMENU, MF_DISABLED);
	SetWindowLongPtrA(
		GetConsoleWindow(),
		GWL_STYLE,
		GetWindowLongPtrA(GetConsoleWindow(), GWL_STYLE)
		& ~WS_SIZEBOX & ~WS_MAXIMIZEBOX & ~WS_MINIMIZEBOX
	);

	SetWindowLong(hWnd, GWL_EXSTYLE, WS_EX_TRANSPARENT);

	CONSOLE_CURSOR_INFO cursor_info = { 1,0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
	CONSOLE_SCREEN_BUFFER_INFO buffer_info;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &buffer_info);
	SMALL_RECT rect = buffer_info.srWindow;
	COORD size = { rect.Right + 1,rect.Bottom + 1 };
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), size);
	return;
}

inline fs SetSize() {
	HWND hWnd = GetConsoleWindow();
	HDC hdc = GetDC(hWnd);
	COORD size;
	fs r;
	fs LT;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	long long width = GetSystemMetrics(SM_CXSCREEN);
	long long height = GetSystemMetrics(SM_CYSCREEN);
	COORD font_size = get_font_size();
	LT.X = width / 8;
	LT.Y = height / 12;
	size.X = width * 3 / 4;
	size.Y = height * 5 / 6;
	SetWindowPos(hWnd, HWND_TOPMOST, LT.X, LT.Y, size.X, size.Y, 0);
	r.X = size.X;
	r.Y = size.Y;

	return r;
}

inline VOID RevealConsoleCloseButton(VOID) {
	DeleteMenu(GetSystemMenu(GetConsoleWindow(), TRUE), SC_ARRANGE, MF_ENABLED);
	DeleteMenu(GetSystemMenu(GetConsoleWindow(), TRUE), SC_MINIMIZE, MF_ENABLED);
	DeleteMenu(GetSystemMenu(GetConsoleWindow(), TRUE), SC_MAXIMIZE, MF_ENABLED);
	DrawMenuBar(GetConsoleWindow());

}

#endif