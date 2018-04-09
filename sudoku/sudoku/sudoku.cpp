#include "stdafx.h"

int main(int argc, char* argv[])
{
	exception exc;
	FILE* output_file;
	fopen_s(&output_file, "sudoku.txt", "w");
	if (argc != 3) {
		cout << "illegal numbers of parameters" << endl;
		exit(0);
	}
	if (strcmp(argv[1], "-c") == 0) {
		int numbers = 0;
		string temp = argv[2];
		int i;
		int length = temp.length();
		for (i = 0; i < length; i++) {
			if (temp[i] > '9' || temp[i] < '0') {
				cout << "illegal sudoku number" << endl;
				exit(0);
			}
			else {
				numbers = numbers * 10 + (temp[i] - '0');
			}

		}		
		product s1(numbers);
		s1.produce(output_file);
		fclose(output_file);
	}
	else if (strcmp(argv[1], "-s") == 0) {
		FILE* input_file;
		fopen_s(&input_file, argv[2], "r");

		if (!input_file) {
			cout << "illegal path" << endl;
			exit(0);
		}
		product s1(0);
		s1.solve(input_file, output_file);
		fclose(input_file);
		fclose(output_file);
	}
	else {
		cout << "illegal parameter" << endl;
		exit(0);
	}
	return 0;
}