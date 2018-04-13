#include "stdafx.h"
#include "CppUnitTest.h"
#include "../sudoku/choose.h"
#include "../sudoku/maker.h"
#include "../sudoku/solver.h"
#include "../sudoku/choose.cpp"
#include "../sudoku/maker.cpp"
#include "../sudoku/solver.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			FianlMaker fm;
			int a[2][9] = {
				{ 9,8,7,6,5,4,3,2,1 },
			{ 1,2,3,4,5,6,7,8,9 } };
			for (int i = 0; i < 2; i++) {
				for (int j = 0; j < 9; j++) {
					fm.rowExchange(a[i][j], a[j][i]);
				}
			}
			for (int i = 0; i < 9; i++) {
				Assert::AreEqual(i + 1, a[0][i]);
				Assert::AreEqual(9 - i, a[1][i]);
			}
		}
		TEST_METHOD(TestMethod2) {
			FianlMaker fm;
			int a[9][9] = {
				{ 1,2,3,4,5,6,7,8,9 },
			{ 1,2,3,4,5,6,7,8,9 },
			{ 1,2,3,4,5,6,7,8,9 },
			{ 1,2,3,4,5,6,7,8,9 },
			{ 1,2,3,4,5,6,7,8,9 },
			{ 1,2,3,4,5,6,7,8,9 },
			{ 1,2,3,4,5,6,7,8,9 },
			{ 1,2,3,4,5,6,7,8,9 },
			{ 1,2,3,4,5,6,7,8,9 } };
			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					fm.rowExchange(a[i][j], a[j][i]);
				}
			}
			for (int i = 0; i < 9; i++) {
				Assert::AreEqual(2, a[i][0]);
				Assert::AreEqual(1, a[i][1]);
			}
		}

	};
}