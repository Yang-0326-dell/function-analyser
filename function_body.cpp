#ifndef FUNCTION_BODY_CPP
#define FUNCTION_BODY_CPP
#include "function_body.h"
#include "Header.h"

structure::structure(){}

bool structure::match_bracket(Struct *st)
{
	start:
	//LATEST
	bool if_var_find =false;
	for (char &i : variator) {
		if (i == 'x' || i == 'y') {
			if_var_find = true;
			break;
		}
	}
	if (if_var_find==false) {
		std::regex reg0("[0123456789.]*");
		if (regex_match(variator, reg0)) {
			if_bottom_touched = true;
			operate = NON;
			st->operate = NON;
			st->var = stof(variator);
			st->variator = variator;
			return 0;
		}
	}

	if (variator[0] == INV || variator[0] == REC || variator[0] == SIN || variator[0] == COS || variator[0] == LG || variator[0] == LN || variator[0] == ASIN|| variator[0] == ACOS || variator[0] == ATAN || variator == "x"|| variator == "y") {
		handle_spec(st);
	}
	//else if (variator[0] == '-') {
	//	variator[0] = INV;
	//	goto start;
	//}
	else if (variator[0] == '+') {
		variator = "0" + variator;
	}
	else {
		//OLDER
		//cout << variator << endl;
		struct bra {
			short start;
			short end;
		};
		struct sym {
			bool sym;
			short pos;
		};
		//mark a couple of bracklets as a whole part    PS..这一段绝逼没bug
		vector<bra> positions;
		//these are to record specific symbol in passing:)
		vector<sym> add_list;
		vector<sym> mul_list;
		vector<short> mod_list;
		vector<short> sin_list;
		vector<short> cos_list;
		vector<short> tan_list;
		//vector<short> asin_list;
		//vector<short> acos_list;
		//vector<short> atan_list;
		vector<short> log_list;
		vector<short> pow_list;

		short sum = 0;
		short open = 0;	//save the position of the open bracklet
		bool flag_1 = 0;	//check if the open bracklet
		for (short i = 0; i < variator.size(); i++) {
			char tmp = variator[i];
			if (tmp == '(') {
				if (flag_1 == 0) {
					open = i;
				}
				flag_1 = 1;
				sum++;
			}
			else if (tmp == ')') {
				sum--;
			}
			if (sum == 0) {
				if (flag_1 == 1) {
					positions.push_back({ open,i });
					flag_1 = 0;
				}
			}
		}
		//firstly, divide by "+" and "-"(但是好像不是)  PS..这一段也绝逼没问题(翻车次数=9)
		vector<string> divided_content;
		if (positions.size() != 0) {
			for (short i = 0; i < positions[0].start; i++) {
				divided_content.push_back({ variator[i] });
			}
			for (short i = 0; i < positions.size(); i++) {
				divided_content.push_back("");
				short divided_content_size = divided_content.size();
				for (short j = positions[i].start; j <= positions[i].end; j++) {
					divided_content[divided_content_size - 1] += variator[j];
				}
				if (i != positions.size() - 1) {
					for (short j = positions[i].end + 1; j < positions[i + 1].start; j++) {
						divided_content.push_back({ variator[j] });
					}
				}
				else {
					for (short j = positions[i].end + 1; j < variator.size(); j++) {
						divided_content.push_back({ variator[j] });
					}
				}
			}
		}
		else {
			for (short i = 0; i < variator.size(); i++) {
				divided_content.push_back({ variator[i] });
			}
		}

		//secondly, check */ or log^ or lglnsincostan
		for (short i = 0; i < divided_content.size(); i++) {
			if (divided_content[i].size() == 1) {
				char tmp = divided_content[i][0];
				if (tmp == '+') {
					add_list.push_back({ 1,i });
				}
				else if (tmp == '-') {
					add_list.push_back({ 0,i });
				}
				else if (tmp == '*') {
					mul_list.push_back({ 1, i });
				}
				else if (tmp == '/') {
					mul_list.push_back({ 0,i });
				}
				else if (tmp == '%') {
					mod_list.push_back(i);
				}
				else if (tmp == '^') {
					pow_list.push_back(i);
				}
				else if (tmp == LOG) {
					log_list.push_back(i);
				}
			}
		}
		//Thirdly, DIVIDE COMPLETELY PS.这一段大改22次
		if (add_list.size() != 0) {
			string str = "";
			short reb = 0;//Check if brackets should be removed
			if (add_list[0].pos != 0) {
				branch.resize(add_list.size() + 1);
				operate = ADD;
				for (short j = 0; j < add_list[0].pos; j++) {
					str.append(divided_content[j]);
					reb++;
				}
				if (reb == 1 && str[0] == '(') {
					string::iterator it = str.begin();
					str.erase(it);
					str.pop_back();
				}//removed
				branch[0].variator = str;
				branch[0].level = level + 1;
				st->operate = ADD;
				Struct st_;
				st_.level = level + 1;
				st_.variator = str;
				st->branch.push_back(st_);
			}
			else {
				branch.resize(add_list.size());
			}

			//cout << 0 << " " << str << endl;
			for (short i = 0; i < add_list.size(); i++) {
				str = "";
				reb = 0;

				if (add_list[i].sym == 0) {
					str.append({ INV });
					reb = 2;
				}
				if (i != add_list.size() - 1) {
					for (short j = add_list[i].pos + 1; j < add_list[i + 1].pos; j++) {
						str.append(divided_content[j]);
						reb++;
					}
				}
				else {
					for (short j = add_list[i].pos + 1; j < divided_content.size(); j++) {
						str.append(divided_content[j]);
						reb++;
					}
				}
				if (reb==1 && str[0] == '(') {
					string::iterator it = str.begin();
					str.erase(it);
					str.pop_back();
				}//removed
				if (add_list[0].pos != 0) {
				branch[i + 1].variator = str;
				branch[i + 1].level = level + 1;
				}
				else {
					branch[i ].variator = str;
					branch[i ].level = level + 1;
				}
				st->operate = ADD;
				Struct st_;
				st_.level = level + 1;
				st_.variator = str;
				st->branch.push_back(st_);
				//cout << i + 1 << " " << str << endl;
			}

		}
		else if (mul_list.size() != 0) {
			branch.resize(mul_list.size() + 1);
			operate = MUL;
			string str = "";
			short reb = 0;//Check if............
			for (short j = 0; j < mul_list[0].pos; j++) {
				str.append(divided_content[j]);
				reb++;
			}
			if (reb == 1 && str[0] == '(') {
				string::iterator it = str.begin();
				str.erase(it);
				str.pop_back();
			}//removed
			branch[0].variator = str;
			branch[0].level = level + 1;
			st->operate = MUL;
			Struct st_;
			st_.level = level + 1;
			st_.variator = str;
			st->branch.push_back(st_);
			for (short i = 0; i < mul_list.size(); i++) {
				str = "";
				reb = 0;
				if (mul_list[i].sym == 0) {
					str.append({ REC });
					reb = 2;
				}
				if (i != mul_list.size() - 1) {
					for (short j = mul_list[i].pos + 1; j < mul_list[i + 1].pos; j++) {
						str.append(divided_content[j]);
						reb++;
					}
				}
				else {
					for (short j = mul_list[i].pos + 1; j < divided_content.size(); j++) {
						str.append(divided_content[j]);
						reb++;
					}
				}

				if (reb == 1 && str[0]== '(') {
					string::iterator it = str.begin();
					str.erase(it);
					str.pop_back();
				}//removed
				branch[i + 1].variator = str;
				branch[i + 1].level = level + 1;
				st->operate = MUL;
				Struct st_;
				st_.level = level + 1;
				st_.variator = str;
				st->branch.push_back(st_);
			}
		}
		else if (pow_list.size() != 0) {
		st->branch.resize(2);
		branch.resize(2);
		string str1 = "";
		string str2 = "";
		int rem1 = 0, rem2 = 0;//Check if....
		for (short i = 0; i < pow_list[0]; i++) {
			str1.append(divided_content[i]);
			rem1++;
		}
		for (short i = pow_list[0] + 1; i < divided_content.size(); i++) {
			str2.append(divided_content[i]);
			rem2++;
		}
		cout << str1 << " " << str2 << endl;
		if (rem1 == 1 && str1[0] == '(') {
			string::iterator it = str1.begin();
			str1.erase(it);
			str1.pop_back();
		}
		if (rem2 == 1 && str2[0] == '(') {
			string::iterator it = str2.begin();
			str2.erase(it);
			str2.pop_back();
		}
		st->branch[0].variator = str1;
		st->branch[1].variator = str2;
		st->branch[0].level = level + 1;
		st->branch[1].level = level + 1;
		st->operate = POW;
		branch[0].variator = str1;
		branch[1].variator = str2;
		branch[0].level = level + 1;
		branch[1].level = level + 1;
		operate = POW;
}
		else if (log_list.size() != 0) {

		st->branch.resize(2);
		branch.resize(2);
		string str1 = "";
		string str2 = "";
		int rem1 = 0, rem2 = 0;//Check if...
		for (short i = 0; i < log_list[0]; i++) {
			str1.append(divided_content[i]);
			rem1++;
		}
		for (short i = log_list[0] + 1; i < divided_content.size(); i++) {
			str2.append(divided_content[i]);
			rem2++;
		}
		if (rem1 == 1 && str1[0] == '(') {
			string::iterator it = str1.begin();
			str1.erase(it);
			str1.pop_back();
		}
		if (rem2 == 1 && str2[0] == '(') {
			string::iterator it = str2.begin();
			str2.erase(it);
			str2.pop_back();
		}
		st->branch[0].variator = str1;
		st->branch[1].variator = str2;
		st->branch[0].level = level + 1;
		st->branch[1].level = level + 1;
		st->operate = LOG;
		branch[0].variator = str1;
		branch[1].variator = str2;
		branch[0].level = level + 1;
		branch[1].level = level + 1;
		operate = LOG;
}

	}

	//Check if it touches the bottom
	if (branch.size() != 0) {
		vector<structure>::iterator it = branch.begin();
		short it_st = 0;
		while (it != branch.end()) {
			if (it->variator == "x") {//第一次没检测到是因为上上面那句话加到下面的else里面去了
				it->variator = VAR1;
				it->operate = VAR1;
				it->if_bottom_touched = true;
				st->branch[it_st].variator = VAR1;
				st->branch[it_st].operate = VAR1;
				st->branch[it_st].if_bottom_touched = true;
			}
			else if (it->variator == "y") {
				it->variator = VAR2;
				it->operate = VAR2;
				it->if_bottom_touched = true;
				st->branch[it_st].variator = VAR2;
				st->branch[it_st].operate = VAR2;
				st->branch[it_st].if_bottom_touched = true;
			}
			else {
				string::iterator it1 = find(it->variator.begin(), it->variator.end(), 'x');
				string::iterator it2 = find(it->variator.begin(), it->variator.end(), 'y');
				if (it1 == it->variator.end() && it2 == it->variator.end()) {
					it->if_bottom_touched = true;
					st->branch[it_st].if_bottom_touched = true;
					std::regex reg("(-)?[0-9\.]*"); 
					if (regex_match(it->variator, reg)) {
						it->operate = NON;
						st->branch[it_st].operate = NON;
						st->branch[it_st].var = stof(it->variator);
					}
					else {
						bool if_var_fin = false;
						for (char& i : it->variator) {
							if (i == 'x' || i == 'y') {
								if_var_fin = true;
								break;
							}
						}
						if(if_var_fin==false) {//改了起码100次
							st->branch[it_st].operate = CON;
							long double con = 0;
							function_body cal_con;
							cal_con.result.operate = CON;
							cal_con.construct(it->variator);
							st->branch[it_st].var = cal_con.calculate(cal_con.result).result;
							it->operate = NON;
							st->branch[it_st].operate = NON;
							//cout << "var=" << st->variator << endl;
						}
					}
				}
			}
			it++;
			it_st++;
		}
	}
	return false;
}

bool structure::construct(Struct *s) 
{
	if (if_bottom_touched == false) {
		match_bracket(s);//ATTENTION: CHECK HERE!
	}
	//Only non-sin/cos/tan/^ available!!!!!!!!!
if (branch.size()!=0) {
	cout << s->branch.size() << endl;
		for (short i = 0; i < branch.size();i++) {
			cout << "level=" << s->level << " " << s->operate <<" branch" << i <<endl;
			branch[i].construct(&s->branch[i]);
		}
	}
	else {
		if_bottom_touched = 1;
		s->if_bottom_touched = 1;
}
		return false;
}

bool structure::delete_char(short start, short end, string str) {
	string::iterator k = str.begin();
	short i = 0;
	while (k != str.end()) {
		if(i>=start&&i<end){
			str.erase(*k);
		}
		i++;
	}
	return false;
}

bool structure::handle_spec(Struct *st) {
	if (variator == "x") {
		if_bottom_touched = true;
		variator = VAR1;
		operate = VAR1;
		branch.resize(0);
		st->variator = VAR1;
		st->operate = VAR1;
		st->if_bottom_touched = true;
		st->level = 0;
		st->branch.resize(0);
	}
	else if (variator == "y") {
		if_bottom_touched = true;
		variator = VAR2;
		operate = VAR2;
		branch.resize(0);
		st->variator = VAR2;
		st->operate = VAR2;
		st->if_bottom_touched = true;
		st->level = 0;
		st->branch.resize(0);
	}
else
	{
		branch.resize(1);
		branch[0].level = level + 1;
		branch[0].variator = variator;
		operate = variator[0];
		branch[0].variator.erase(branch[0].variator.begin());
		if (branch[0].variator[0] == '(') {
			branch[0].variator.erase(branch[0].variator.begin());
			branch[0].variator.pop_back();
		}
		st->branch.resize(1);
		st->branch[0].level = level + 1;
		st->branch[0].variator = branch[0].variator;
		st->operate = variator[0];
	}
	
	return true;
}

function_body::function_body(){}

bool function_body::convert() {
	string function_ = "";//Prevent being over modified
	for (short i = 0; i < function.size();i++) {
		char tmp = function[i];
		if (tmp == 's' || tmp == 'c' || tmp == 't'||tmp=='l') {//ATTENTION!!!If other symbols are added, check here!
			if (i < function.size() - 3) {
				string tri = { function[i],function[i + 1],function[i + 2] };
				char test = i >= 1 ? function[i - 1] : 0;
				if (tri == "sin") {
					if (test != 'a') {
						function_ += SIN;
						i += 2;
					}
					else {
						function_.pop_back();
						function_ += ASIN;
						i += 3;
					}
				}
				else if (tri == "cos") {
					if (test != 'a') {
						function_ += COS;
						i += 2;
					}
					else {
						function_.pop_back();
						function_ += ACOS;
						i += 3;
					}
				}
				else if (tri == "tan") {
					if (test != 'a') {
						function_ += TAN;
						i += 2;
					}
					else {
						function_.pop_back();
						function_ += ATAN;
						i += 3;
					}
				}
				else if (tri[0] == 'l') {
					if (tri == "log") {
						function_ += LOG;
						i += 2;
					}
				}
			}
			if (i < function.size() - 2 && function[i] == 'l') {
				string tri = { function[i],function[i + 1] };
				if (tri[1] == 'n') {
					cout << 518 << endl;
					function_ += LN;
					i += 1;
				}
				else if (tri[1] == 'g') {
					function_ += LG;
					i += 1;
				}
			}
		}
		else {
			function_ += tmp;
		}
	}
	cout << function_ << endl;
	function1 = function_;
	return false;
}

bool function_body::construct()
{
	analyzed.variator = function1;
	result.variator = function1;
	analyzed.construct(&result);
	return true;
}
bool function_body::construct(string c)
{
	analyzed.variator =c;
	result.variator = c;
	analyzed.construct(&result);
	//cout << sizeof(analyzed.branch) << endl;
	return true;
}

bool function_body::output1(Struct s) {
	short x = s.level;
	string tmp = s.variator;
	for (int i = 0; i < x * 13 + 3; i++) {
		cout << " ";
	}
	if (s.operate == ADD) {
		cout << "ADD";
	}
	else if (s.operate == INV) {
		cout << "INV";
	}
	else if (s.operate == MUL) {
		cout << "MUL";
	}
	else if (s.operate == SIN) {
		cout << "SIN";
	}
	else if (s.operate == COS) {
		cout << "COS";
	}
	else if (s.operate == TAN) {
		cout << "TAN";
	}
	else if (s.operate == ASIN) {
		cout << "ASIN";
	}
	else if (s.operate == ACOS) {
		cout << "ACOS";
	}
	else if (s.operate == ATAN) {
		cout << "ATAN";
	}

	else if (s.operate == LOG) {
		cout << "LOG";
	}
	else if (s.operate == LG) {
		cout << "LG";
	}
	else if (s.operate == LN) {
		cout << "LN";
	}
	else if (s.operate == INV) {
		cout << "INV";
	}
	else if (s.operate == NON) {
		cout << "NON";
	}
	else if (s.operate == CON) {
		cout << "CON";
	}
	else if (s.operate == VAR1) {
		cout << "X";
	}
	else if (s.operate == VAR2) {
		cout << "Y";
	}
	else if (s.operate == POW) {
		cout << "POW";
	}
	cout << endl;

	if (tmp.size() > CHARACTER_MAX) {
		for (short i = 0; i < tmp.size() - CHARACTER_MAX; i++) {
			tmp.pop_back();
		}
	}
	if (tmp.size() > CHARACTER_MAX / 2) {
		string tmp1 = tmp;
		string tmp2 = tmp;
		for (short i = 0; i < tmp1.size() - CHARACTER_MAX / 2; i++) {
			tmp1.pop_back();
		}
		for (short i = 0; i <= CHARACTER_MAX / 2; i++) {
			tmp2.erase(tmp2.begin());
		}
		for (int i = 0; i < x * 13 + 3; i++) {
			cout << " ";
		}
		cout << tmp1 << endl;
		for (int i = 0; i < x * 13 + 3; i++) {
			cout << " ";
		}
		cout << tmp2 << endl;
	}
	else {
		for (int i = 0; i < x * 13; i++) {
			cout << " ";
		}

		cout << "   " << tmp << endl;
	}

	if (s.branch.size() != 0) {
		for (short id = 0; id < s.branch.size(); id++) {
			output1(s.branch[id]);
		}
	}

	return 1;

}

function_body::re function_body::calculate(Struct s) {
	unsigned char o = s.operate;
	if (o == VAR1) {
		return { NON_FLAG,ori };

	}
	else if (o == NON) {
			return{ NON_FLAG,s.var };
		
	}
	else if (o == INV) {
		return { NON_FLAG, -calculate(s.branch[0]).result };
	}
	else if (o == REC) {
		if (ori != 0) {
			return { NON_FLAG,long double(1) / calculate(s.branch[0]).result };
		}
		else {
			return{ DIVIDED_BY_0,0 };
		}
	}
	else if (o == SIN) {
		return { NON_FLAG, sin(calculate(s.branch[0]).result) };
	}
	else if (o == COS) {
		return { NON_FLAG, cos(calculate(s.branch[0]).result) };
	}
	else if (o == TAN) {
		return { NON_FLAG, tan(calculate(s.branch[0]).result) };
	}
	else if (o == ASIN) {
		return { NON_FLAG, asin(calculate(s.branch[0]).result) };
	}
	else if (o == ACOS) {
		return { NON_FLAG, acos(calculate(s.branch[0]).result) };
	}
	else if (o == ATAN) {
		return { NON_FLAG, atan(calculate(s.branch[0]).result) };
	}
	else if (o == LG) {
		re tmp = calculate(s.branch[0]);
		if (tmp.result > 0)
			return { NON_FLAG, log10(tmp.result) };
		else {
			return { LNERROR ,long double(-INFINITY) };
		}
	}
	else if (o == LN) {
		re tmp = calculate(s.branch[0]);
		if (tmp.result > 0)
			return { NON_FLAG, log(tmp.result) };
		else {
			return { LNERROR ,long double(-INFINITY) };
		}
	}
	else {
		//long double result = 0;
		//short fl = 1;
		re joint;
		if (o == ADD) {
			for (Struct i : s.branch) {
				re tmp=calculate(i);
				joint.flag *= tmp.flag;
				joint.result += tmp.result;
			}
		}
		else if (o == MUL) {
			joint.result = 1;
			for (Struct i : s.branch) {
				re tmp = calculate(i);
				joint.flag *= tmp.flag;
				joint.result *= tmp.result;
			}
		}
		else if (o == POW) {
			re tmp1 = calculate(s.branch[0]);
			re tmp2 = calculate(s.branch[1]);
			joint.flag = tmp1.flag * tmp2.flag;
			joint.result = pow(tmp1.result, tmp2.result);
		}
		else if (o == LOG) {
			re tmp1 = calculate(s.branch[0]);
			re tmp2 = calculate(s.branch[1]);
			if (tmp1.result > 0 && tmp2.result > 0) {
			joint.flag = tmp1.flag * tmp2.flag;
			//joint.result = log(tmp2.result)/log(tmp1.result);
			}
			else {
				return { LNERROR,-INFINITY };
			}
		}
		else if (o == CON) {
			joint = calculate(s.branch[0]);
			cout << "Congratulations! You have triggered an error. Please contact 3623103933 at QQ or https://t.me/invisible2006y. 不胜感激！" << endl;
		}
		//cout<<"result="<<result<<" "<<"flag="<<fl<<endl;
		return joint;
	}
}
#endif
