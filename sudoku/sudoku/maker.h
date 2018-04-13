#pragma once

#include "stdafx.h"



class FianlMaker {
public:
	void make(int n);
	int num, count;
	int table[9][9];
	int temp[9][9];
	void record();
	void rowExchange(const int& r1, const int& r2);
	void colExchange(const int& c1, const int& c2);
	void combina(const int& c1, const int& c2, const int& c3, const int& r1, const int& r2, const int& r3);
};
