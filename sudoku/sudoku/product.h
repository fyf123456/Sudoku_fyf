#pragma once
#include "stdafx.h"
using namespace std;
class product
{
public:
	int number;	//控制数独生成数目
	product(int a);
	~product();

	void produce(FILE* output);	//顶层生成number个终局数独
	void produce_72(FILE* output, int(&seed)[MAX_LENGTH], int(&ans)[MAX_OUTPUT_MATRIX_NUM][MAX_LENGTH][MAX_LENGTH]);	//生成一组72个数独
	void produce_36(int(&src)[MAX_OUTPUT_MATRIX_NUM][MAX_LENGTH][MAX_LENGTH], int sample);	//生成一组36个数独
	void produce_6(int(&src)[MAX_OUTPUT_MATRIX_NUM][MAX_LENGTH][MAX_LENGTH], int sample);	//生成一组 6个数独
	void produce_one(FILE* output, int(&seed)[MAX_LENGTH], int(&ans)[MAX_LENGTH][MAX_LENGTH]);	//生成一个终局数独
	void move_3_3(int* src, int* tar);
	void move_9_9(int(&src)[MAX_LENGTH], int(&tar)[MAX_LENGTH]);
	void refresh(int(&seed)[MAX_LENGTH]);		//更新种子
	void swap_2_line(int(&src)[MAX_LENGTH][MAX_LENGTH], int(&tar)[MAX_LENGTH][MAX_LENGTH], int srcl, int tarl);
	bool solve(FILE* input, FILE* output);	//计算输入文件中所有的数独结果
	bool solve_one(FILE* input, FILE* output);	//计算一个数独结果
	void refresh_matrix(bitset<MAX_LENGTH + 1>(&matrix)[MAX_LENGTH][MAX_LENGTH], int i, int j, int aim);	//更新信息矩阵
	void backdate(int(&ans)[MAX_LENGTH][MAX_LENGTH], bitset<MAX_LENGTH + 1>(&matrix)[MAX_LENGTH][MAX_LENGTH], FILE* output, bool& done);	//回溯算法
	void print2file(int(&ans)[MAX_OUTPUT_MATRIX_NUM][MAX_LENGTH][MAX_LENGTH], FILE* output, int num);
	void print2file(int(&ans)[MAX_LENGTH][MAX_LENGTH], FILE* output);
	bool testMatrix(int(&matrix)[MAX_LENGTH][MAX_LENGTH], int i, int j);
};