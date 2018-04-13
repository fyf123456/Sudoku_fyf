#include "stdafx.h"


int Left[num], Right[num], Up[num], Down[num];	// ÿ��Ԫ�ص�4������������൱�������еļ�ͷ��
int Col[num];		// ��¼ÿ��Ԫ�ص��б�Ԫ��
int Row[num];		// ��¼ÿ��Ԫ�����ڵ�01��������
int Size[maxcol];	// ��¼ÿ�еġ�1��Ԫ�ظ���
int Head[maxrow];	// ��¼ÿ�е�һ����1��Ԫ��
static char str[163];
static int index;

char* SudokuSolver::solve(char ch[]) {
	index = 0;
	transform(table, ch);
	link();
	int select = 0;
	for (size_t i = 0; i < 9; i++) {
		for (size_t j = 0; j < 9; j++) {
			int k = table[i][j];
			if (k) {	// ����������Ŀ�Ѹ����ֵ��б�ѡ
				int row = i * 81 + j * 9 + k - 1;
				select++;
				remove(Col[Head[row]]);		// �Ƴ�������Ԫ�ؼ������Ԫ��
				for (int u = Right[Head[row]]; u != Head[row]; u = Right[u])	// �Ƴ���������Ԫ�ؼ������Ԫ��
					remove(Col[u]);
			}
		}
	}

	(dfs(select + 1));

	for (size_t i = 0; i < 9; i++) {
		for (size_t j = 0; j < 8; j++) {
			str[index++] = char(table[i][j] + '0');
			str[index++] = ' ';
		}
		str[index++] = (table[i][8] + '0');
		str[index++] = '\n';
	}
	str[index++] = '\n';
	return str;
}

void SudokuSolver::transform(int table[][9], char ch[]) {
	int index = 0;
	for (size_t i = 0; i < 9; i++)
		for (size_t j = 0; j < 9; j++)
			table[i][j] = ch[index++] - '0';
	return;
}

void SudokuSolver::link() {
	/* �����б�Ԫ�� */
	for (size_t i = 0; i < maxcol; i++) {
		Left[i] = i - 1;
		Right[i] = i + 1;
		Up[i] = Down[i] = i;
		Row[i] = 0;
		Col[i] = i;
		Size[i] = 0;
	}
	/* ����HeadԪ�� */
	Left[0] = maxcol - 1;
	Right[maxcol - 1] = 0;
	no = maxcol;
	/* ���ӡ�1��Ԫ�� */
	for (size_t i = 0; i < 9; i++) {
		for (size_t j = 0; j < 9; j++) {	// ����9x9����
			int k = table[i][j];
			if (k) {
				for (size_t t = 1; t <= 4; t++) {	// ÿ����0���ֻ���01�����в���4����1��Ԫ��
					Left[no + t] = no + t - 1;
					Right[no + t] = no + t + 1;
					Row[no + t] = i * 81 + j * 9 + k - 1;
				}
				Left[no + 1] = no + 4;
				Right[no + 4] = no + 1;
				Head[Row[no + 1]] = no + 1;
				/* ��4��Ԫ�ز��������� */
				insertNode(i * 9 + j + 1, no + 1);
				insertNode(81 + i * 9 + k, no + 2);
				insertNode(81 * 2 + j * 9 + k, no + 3);
				insertNode(81 * 3 + (i / 3 * 3 + j / 3) * 9 + k, no + 4);
				no += 4;
			}
			else {	// ��λ��Ϊ0��������
				for (size_t k = 1; k <= 9; k++) {	// ����9���
					for (size_t t = 1; t <= 4; t++) {	// ���ɲ��������ǵ�Ԫ��
						Left[no + t] = no + t - 1;
						Right[no + t] = no + t + 1;
						Row[no + t] = i * 81 + j * 9 + k - 1;
					}
					Left[no + 1] = no + 4;
					Right[no + 4] = no + 1;
					Head[Row[no + 1]] = no + 1;
					insertNode(i * 9 + j + 1, no + 1);
					insertNode(81 + i * 9 + k, no + 2);
					insertNode(81 * 2 + j * 9 + k, no + 3);
					insertNode(81 * 3 + (i / 3 * 3 + j / 3) * 9 + k, no + 4);
					no += 4;
				}
			}
		}
	}
}

void SudokuSolver::insertNode(int col, int no) {	// ��no��Ԫ����ӵ�col����
													/* ��Ԫ��col��Down[col]֮�����no */
	Up[Down[col]] = no;
	Down[no] = Down[col];
	Up[no] = col;
	Down[col] = no;
	Size[col]++;
	Col[no] = col;
}

void SudokuSolver::remove(int col) {	// ���б�Ԫ���Ƴ����Ԫ��
										/* �Ƴ�col�б�Ԫ�� */
	Left[Right[col]] = Left[col];
	Right[Left[col]] = Right[col];
	/* �Ƴ�col�С�1��Ԫ������ͬ��Ԫ�� */
	for (size_t i = Down[col]; i != col; i = Down[i]) {	// ����ɾ
		for (size_t j = Right[i]; j != i; j = Right[j]) {	// ����ɾ
			Up[Down[j]] = Up[j];
			Down[Up[j]] = Down[j];
			Size[Col[j]]--;
		}
	}
}

void SudokuSolver::restore(int col) {
	/* �ָ�col�б�Ԫ�� */
	Left[Right[col]] = Right[Left[col]] = col;
	/* �ָ�col�С�1��Ԫ������ͬ��Ԫ�� */
	for (size_t i = Up[col]; i != col; i = Up[i]) {		// �ָ�˳�����Ƴ�˳���෴
		for (size_t j = Left[i]; j != i; j = Left[j]) {
			Up[Down[j]] = Down[Up[j]] = j;
			Size[Col[j]]++;
		}
	}
}

bool SudokuSolver::dfs(int select) {
	if (select > 81)	// ��ѡ��
		return true;
	/* �����б�Ԫ�أ�ѡһ��Ԫ�����ٵ��У������ʵͣ� */
	int col = 0;
	int min = INT_MAX;
	for (size_t i = Right[0]; i != 0; i = Right[i]) {
		int size = Size[i];
		if (size == 0)
			return false;
		if (size < min) {
			min = size;
			col = i;
		}
	}
	remove(col);
	/* �������и���1��Ԫ��,�������γ���,ʧ����ָ����Ƴ��Ľ�� */
	for (size_t i = Down[col]; i != col; i = Down[i]) {
		int row = Row[i];
		table[row / 81][row % 81 / 9] = row % 9 + 1;	// ���ݸ�Ԫ�ص�����������
		for (size_t j = Right[i]; j != i; j = Right[j])	// �Ƴ����Ԫ��ͬ��Ԫ�ص��� 
			remove(Col[j]);
		if (dfs(select + 1))	// ��ѡ����+1���ݹ�
			return true;
		for (size_t j = Left[i]; j != i; j = Left[j])	// ����false��ָ��ղŵ��Ƴ���˳���෴
			restore(Col[j]);
	}
	restore(col);
	return false;
}