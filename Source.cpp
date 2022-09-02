#include "Header.h"
#include "function_body.h"
#include "control.cpp"
#include "graphic.h"

int main()
{
	begin:
	function_body test;
	cout << "input function:f(x)=";
	cin >> test.function;
	test.convert();
	test.construct();
	bool i;
	CONTROL_CPP::input_num("Need ouput analyzation?\n0.no/1.yes\n",&i);
	if (i) {
		system("cls");
		test.output1(test.result);
	}
	Graphic gr;
	bo1:
	gr.ini();
	cout << "f(x)=" << test.function << endl;
	gr.draw_axis();
	for (double i = -gr.width /2; i < gr.width / 2; i+=gr.precision) {
		test.ori = i ;//default beginning at middle
		gr.draw_fun(i , double(test.calculate(test.result).result));
		//cout << i << " "<<test.calculate(test.result).result << endl;
	}
	string qq = "";
	cin >> qq;
	bool redr = 0;
	
	input_num("1.redraw;0.end.", &redr);
	if (redr == 1) {
		gr.redraw();
		goto bo1;
	}
	bool quit = 0;
	input_num("1.restart;0.quit.", &quit);
	if (quit == true) {
		goto begin;
	}
	return 0;
}