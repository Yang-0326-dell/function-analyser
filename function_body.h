#ifndef FUNCTION_BODY_H
#define FUNCTION_BODY_H
#include "Header.h"
#include <string>


//inherit the function
struct Struct {
	vector<Struct> branch;
	bool if_bottom_touched = false;
	short level = 0;
	unsigned char operate = NON;
	std::string variator;
	long double var=0;
};
class structure {
public:
	structure();
	bool if_bottom_touched = false;
	short level=0;
	short operate=NON;
	std::string variator;
	std::vector<structure> branch;
	bool construct(Struct*);
	bool match_bracket(Struct*);

private:
	bool delete_char(short, short,string);//左闭右开
	bool handle_spec(Struct*);
};


class function_body
{
public:
	string function;
	string function1;
	structure analyzed;
	Struct result;
	long double domain[2];
	struct re{
		short flag = 0;
		long double result=0;
	};
	long double ori = 0;
	function_body();
	bool construct();
	bool construct(string);
	bool convert();
	bool output1(Struct);//width, height
	re calculate(Struct);
};

#endif
