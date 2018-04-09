#include "stdafx.h"



void InputHandler::check(int argc, char ** argv) {
	if (argc == 3) {
		string parameter1 = argv[1];
		string parameter2 = argv[2];
		if (parameter1 == "-c") {
			int n = isNum(parameter2);
			if (n <= 0 || n > 1000000)
				cout << "illegal sudoku number£¡" << endl;
			else {
				FianlMaker fm;
				fm.make(n);
				cout << "success !" << endl;
			}
		}
		else if (parameter1 == "-s") {
			ifstream in(parameter2);
			if (!in.is_open()) {
				cout << "illegal path" << endl;
				return;
			}
			char ch[81];
			char c;
			int count = 0;
			SudokuSolver ss;
			FILE* out = fopen("sudoku.txt", "wt");
			while (in.get(c)) {	
				if (isdigit(c)) {
					ch[count++] = c;
				}
				if (count == 81) {
					count = 0;
					fputs(ss.solve(ch), out);
				}
			}
			in.close();
			if (count != 0) {
				const char *str;
				str = "illegal numbers of parameters£¡";
				fputs(str, out);
				cout << str << endl;
			}
			else
				cout << "success !" << endl;
			fclose(out);
		}
		else {
			cout << "illegal £¡" << endl;
		}
	}
	else {
		cout << "illegal! " << endl;
	}
	return;
}

int InputHandler::isNum(const string & s) {
	size_t size = s.size();
	if (size > 7)
		return 0;
	for (size_t i = 0; i < size; i++) {
		int ascii = int(s[i]);
		if (ascii >= 48 && ascii <= 57)
			continue;
		else
			return 0;
	}
	return stoi(s);
}