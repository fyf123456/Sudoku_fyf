#pragma once
#include "stdafx.h"
using namespace std;
class product
{
public:
	int number;	//��������������Ŀ
	product(int a);
	~product();

	void produce(FILE* output);	//��������number���վ�����
	void produce_72(FILE* output, int(&seed)[MAX_LENGTH], int(&ans)[MAX_OUTPUT_MATRIX_NUM][MAX_LENGTH][MAX_LENGTH]);	//����һ��72������
	void produce_36(int(&src)[MAX_OUTPUT_MATRIX_NUM][MAX_LENGTH][MAX_LENGTH], int sample);	//����һ��36������
	void produce_6(int(&src)[MAX_OUTPUT_MATRIX_NUM][MAX_LENGTH][MAX_LENGTH], int sample);	//����һ�� 6������
	void produce_one(FILE* output, int(&seed)[MAX_LENGTH], int(&ans)[MAX_LENGTH][MAX_LENGTH]);	//����һ���վ�����
	void move_3_3(int* src, int* tar);
	void move_9_9(int(&src)[MAX_LENGTH], int(&tar)[MAX_LENGTH]);
	void refresh(int(&seed)[MAX_LENGTH]);		//��������
	void swap_2_line(int(&src)[MAX_LENGTH][MAX_LENGTH], int(&tar)[MAX_LENGTH][MAX_LENGTH], int srcl, int tarl);
	bool solve(FILE* input, FILE* output);	//���������ļ������е��������
	bool solve_one(FILE* input, FILE* output);	//����һ���������
	void refresh_matrix(bitset<MAX_LENGTH + 1>(&matrix)[MAX_LENGTH][MAX_LENGTH], int i, int j, int aim);	//������Ϣ����
	void backdate(int(&ans)[MAX_LENGTH][MAX_LENGTH], bitset<MAX_LENGTH + 1>(&matrix)[MAX_LENGTH][MAX_LENGTH], FILE* output, bool& done);	//�����㷨
	void print2file(int(&ans)[MAX_OUTPUT_MATRIX_NUM][MAX_LENGTH][MAX_LENGTH], FILE* output, int num);
	void print2file(int(&ans)[MAX_LENGTH][MAX_LENGTH], FILE* output);
	bool testMatrix(int(&matrix)[MAX_LENGTH][MAX_LENGTH], int i, int j);
};