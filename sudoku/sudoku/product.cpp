#include "stdafx.h"
#include "product.h"

using namespace std;


product::product(int a) {
	number = a;
}

product::~product() {}

void product::refresh(int(&seed)[MAX_LENGTH]) {
	int i, temp;
	for (i = MAX_LENGTH - 1; i > 1; i--) {
		if (seed[i] > seed[i - 1]) {
			temp = seed[i];
			seed[i] = seed[i - 1];
			seed[i - 1] = temp;
			break;
		}
	}
}

void product::produce_one(FILE* output, int(&seed)[MAX_LENGTH], int(&ans)[MAX_LENGTH][MAX_LENGTH]) {
	int i;
	for (i = 0; i < MAX_LENGTH; i++) {
		ans[0][i] = seed[i];
	}
	for (i = 3; i < MAX_LENGTH; i += 3) {
		move_3_3(&ans[i - 3][0], &ans[i][0]);
		move_3_3(&ans[i - 3][3], &ans[i][3]);
		move_3_3(&ans[i - 3][6], &ans[i][6]);
	}

	for (i = 0; i < MAX_LENGTH; i += 3) {
		move_9_9(ans[i], ans[i + 1]);
		move_9_9(ans[i + 1], ans[i + 2]);
	}

	//print2file(ans, output);
}

void product::produce_72(FILE* output, int(&seed)[MAX_LENGTH], int(&ans)[MAX_OUTPUT_MATRIX_NUM][MAX_LENGTH][MAX_LENGTH]) {
	produce_one(output, seed, ans[0]);
	produce_36(ans, 0);
	swap_2_line(ans[0], ans[MAX_OUTPUT_MATRIX_NUM / 2], 1, 2);
	produce_36(ans, MAX_OUTPUT_MATRIX_NUM / 2);

}

void product::produce(FILE* output) {
	int i, start;
	int ans[MAX_OUTPUT_MATRIX_NUM][MAX_LENGTH][MAX_LENGTH];
	int seed[MAX_LENGTH] = { 8, 1, 2, 3, 4, 5, 6, 7, 9 };
	for (i = MAX_OUTPUT_MATRIX_NUM; i <= number; i += MAX_OUTPUT_MATRIX_NUM) {
		produce_72(output, seed, ans);
		print2file(ans, output, MAX_OUTPUT_MATRIX_NUM);
		refresh(seed);
	}
	i = i - MAX_OUTPUT_MATRIX_NUM;
	start = number - i;
	produce_72(output, seed, ans);
	print2file(ans, output, start);
}

void product::produce_36(int(&src)[MAX_OUTPUT_MATRIX_NUM][MAX_LENGTH][MAX_LENGTH], int sample) {
	int i;
	swap_2_line(src[sample], src[sample + 6], 4, 5);
	swap_2_line(src[sample], src[sample + 12], 3, 4);
	swap_2_line(src[sample + 12], src[sample + 18], 4, 5);
	swap_2_line(src[sample], src[sample + 24], 3, 5);
	swap_2_line(src[sample + 24], src[sample + 30], 4, 5);
	for (i = 0; i < 6; i++) {
		produce_6(src, sample + 6 * i);
	}

}

void product::produce_6(int(&src)[MAX_OUTPUT_MATRIX_NUM][MAX_LENGTH][MAX_LENGTH], int sample) {
	swap_2_line(src[sample], src[sample + 1], 7, 8);
	swap_2_line(src[sample], src[sample + 2], 6, 7);
	swap_2_line(src[sample + 2], src[sample + 3], 7, 8);
	swap_2_line(src[sample], src[sample + 4], 6, 8);
	swap_2_line(src[sample + 4], src[sample + 5], 7, 8);
}

void product::move_3_3(int* src, int* tar) {
	tar[0] = src[1];
	tar[1] = src[2];
	tar[2] = src[0];
}

void product::move_9_9(int(&src)[MAX_LENGTH], int(&tar)[MAX_LENGTH]) {
	int i;
	for (i = 0; i < MAX_LENGTH; i++) {
		tar[i] = src[(i + 3) % MAX_LENGTH];
	}
}

void product::swap_2_line(int(&src)[MAX_LENGTH][MAX_LENGTH], int(&tar)[MAX_LENGTH][MAX_LENGTH], int s1, int s2) {
	int i, j;
	for (i = 0; i < MAX_LENGTH; i++) {
		for (j = 0; j < MAX_LENGTH; j++) {
			if (i == s1) {
				tar[s1][j] = src[s2][j];
			}
			else if (i == s2) {
				tar[s2][j] = src[s1][j];
			}
			else {
				tar[i][j] = src[i][j];
			}
		}
	}
}

bool product::solve(FILE* input, FILE* output) {
	char temp[MAX_CHARS];
	while (!feof(input)) {
		if (!solve_one(input, output)) {
			return false;
		}
		fgets(temp, MAX_CHARS - 1, input);
	}
	return true;
}

bool product::solve_one(FILE* input, FILE* output) {
	int i, j, k;
	bitset<MAX_LENGTH + 1> matrix[MAX_LENGTH][MAX_LENGTH];
	int ans[MAX_LENGTH][MAX_LENGTH];
	char line[MAX_CHARS];
	int aim;

	//初始化结果矩阵和辅助判断的bitset矩阵
	for (i = 0; i < MAX_LENGTH; i++) {
		for (j = 0; j < MAX_LENGTH; j++) {
			matrix[i][j].flip();
			ans[i][j] = 0;
		}
	}

	//根据输入初始化结果矩阵和bitset矩阵
	for (i = 0; i < MAX_LENGTH; i++) {
		fgets(line, MAX_CHARS, input);
		for (j = 0; j < MAX_LENGTH; j++) {
			ans[i][j] = line[2 * j] - '0';
			if (ans[i][j] != 0) {
				aim = ans[i][j];
				refresh_matrix(matrix, i, j, aim);
			}
		}
	}

	//求解bit count为1的情况
	bool flag = true;

	while (flag) {
		flag = false;
		for (i = 0; i < MAX_LENGTH; i++) {
			for (j = 0; j < MAX_LENGTH; j++) {
				if (matrix[i][j].count() == 2 && ans[i][j] == 0) {
					k = 1;
					while (matrix[i][j][k] == false)	k++;
					ans[i][j] = k;
					refresh_matrix(matrix, i, j, k);
					flag = true;
				}
			}
		}
	}

	//回溯求解剩余空格
	flag = false;
	backdate(ans, matrix, output, flag);
	return flag;
}

void product::refresh_matrix(bitset<MAX_LENGTH + 1>(&matrix)[MAX_LENGTH][MAX_LENGTH], int i, int j, int aim) {
	int k, m, n;
	for (k = 0; k < MAX_LENGTH; k++) {
		matrix[i][k].reset(aim);	//为同行的数做标记
		matrix[k][j].reset(aim);	//为同列的数做标记
	}
	int x = i / 3 * 3;
	int y = j / 3 * 3;
	for (m = 0; m < 3; m++) {
		for (n = 0; n < 3; n++) {
			matrix[x + m][y + n].reset(aim);	//为同宫的数做标记
		}
	}
}

//递归实现的回溯算法
void product::backdate(int(&ans)[MAX_LENGTH][MAX_LENGTH], bitset<MAX_LENGTH + 1>(&matrix)[MAX_LENGTH][MAX_LENGTH], FILE* output, bool& done) {
	int i, j, count = 1;
	//找到第一个空
	for (i = 0; i < MAX_LENGTH; i++) {
		for (j = 0; j < MAX_LENGTH; j++) {
			if (ans[i][j] == 0) {
				break;
			}
		}
		if (j < MAX_LENGTH && ans[i][j] == 0) {
			break;
		}
	}

	//如果没找到空，就输出结果并返回上一层
	if (i == MAX_LENGTH) {
		print2file(ans, output);
		done = true;
		return;
	}

	//遍历这个空的每一个可能的值
	for (; count <= MAX_LENGTH; count++) {
		if (matrix[i][j][count] == true) {
			ans[i][j] = count;
			if (testMatrix(ans, i, j)) {
				backdate(ans, matrix, output, done);
			}
			else {
				ans[i][j] = 0;
				continue;
			}


			if (done) {
				ans[i][j] = 0;
				return;
			}
		}
	}
	//返回上一层前，将这个空清空
	ans[i][j] = 0;
}

void product::print2file(int(&ans)[MAX_OUTPUT_MATRIX_NUM][MAX_LENGTH][MAX_LENGTH], FILE* output, int num) {
	int i, j, k;
	char result[MAX_OUTPUT_CHARS];
	for (i = 0; i < num; i++) {
		for (j = 0; j < MAX_LENGTH; j++) {
			for (k = 0; k < MAX_LENGTH; k++) {
				result[MATRIX_CHARS * i + LINE_CHARS * j + 2 * k] = (char)ans[i][j][k] + '0';
				result[MATRIX_CHARS * i + LINE_CHARS * j + 2 * k + 1] = ' ';
			}
			result[MATRIX_CHARS * i + LINE_CHARS * j + LINE_CHARS - 1] = '\n';

		}
		result[MATRIX_CHARS * i + MATRIX_CHARS - 1] = '\n';
	}

	fwrite(result, sizeof(char), MATRIX_CHARS*num, output);
}

void product::print2file(int(&ans)[MAX_LENGTH][MAX_LENGTH], FILE* output) {
	int j, k;
	char result[MATRIX_CHARS];
	for (j = 0; j < MAX_LENGTH; j++) {
		for (k = 0; k < MAX_LENGTH; k++) {
			result[LINE_CHARS * j + 2 * k] = (char)ans[j][k] + '0';
			result[LINE_CHARS * j + 2 * k + 1] = ' ';
		}
		result[LINE_CHARS * j + LINE_CHARS - 1] = '\n';

	}
	result[MATRIX_CHARS - 1] = '\n';

	fwrite(result, sizeof(char), MATRIX_CHARS, output);
}

bool product::testMatrix(int(&matrix)[MAX_LENGTH][MAX_LENGTH], int i, int j) {
	int k, m, n;
	for (k = 0; k < MAX_LENGTH; k++) {
		if (k != i && matrix[i][j] == matrix[k][j])		return false;
		if (k != j && matrix[i][k] == matrix[i][j])		return false;
	}
	int x = i / 3 * 3;
	int y = j / 3 * 3;
	for (m = 0; m < 3; m++) {
		for (n = 0; n < 3; n++) {
			if ((x + m != i || y + n != j) && matrix[x + m][y + n] == matrix[i][j]) {
				return false;
			}
		}
	}
	return true;
}