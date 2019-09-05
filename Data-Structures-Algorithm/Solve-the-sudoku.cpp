#include <iostream>
bool SolveSudoku(int ** mat);

int main()
{
	//freopen("input.txt", "r", stdin);
	int TC;
	cin >> TC;
	while (TC--) {
		int ** mat = new int*[9];
		for (int i = 0; i < 9; i++) {
			mat[i] = new int[9];
		}
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				cin >> mat[i][j];
			}
		}
		if (SolveSudoku(mat)) {
			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					cout << mat[i][j] << " ";
				}
				//cout << endl;
			}
			cout << endl;
		}
		for (int i = 0; i < 9; i++) {
			delete []mat[i];
		}
		delete[]mat;

	}
	return 0;
}

bool getUnAssignedLocation(int ** mat, int& r, int &c) {
	for (r = 0; r < 9; r++) {
		for (c = 0; c < 9; c++) {
			if (mat[r][c] == 0) {
				return true;
			}
		}
	}
	return false;
}

bool isRowSafe(int ** mat, int r, int val) {
	for (int c = 0; c < 9; c++) {
		if (mat[r][c] == val) {
			return false;
		}
	}
	return true;
}

bool isColSafe(int ** mat, int c, int val) {
	for (int r = 0; r < 9; r++) {
		if (mat[r][c] == val) {
			return false;
		}
	}
	return true;
}
void getLimits(int x, int& start, int& end)
{
	if ((x >= 0) && (x <= 2)) {
		start = 0;
		end = 2;
		return;
	}
	if ((x >= 3) && (x <= 5)) {
		start = 3;
		end = 5;
		return;
	}
	if ((x >= 6) && (x <= 8)) {
		start = 6;
		end = 8;
		return;
	}
	start = -1;
	end = -1;
}

bool isBoxSafe(int ** mat, int r, int c, int val) {
	int rs, re;
	int cs, ce;
	getLimits(r, rs, re);
	getLimits(c, cs, ce);

	for (int i = rs; i <= re; i++) {
		for (int j = cs; j <= ce; j++) {
			if (mat[i][j] == val) {
				return false;
			}
		}
	}
	return true;
}

bool canAssign(int ** mat, int r, int c, int val) {
	return isRowSafe(mat, r, val) && isColSafe(mat, c, val) && isBoxSafe(mat, r, c, val);
}

bool SolveSudoku(int ** mat)
{
	int r, c;
	if (getUnAssignedLocation(mat, r, c) == false) {
		return true;
	}

	for (int val = 1; val <= 9; val++) {
		if (canAssign(mat, r, c, val)) {
			mat[r][c] = val;
			if (SolveSudoku(mat)) {
				return true;
			}
			mat[r][c] = 0;
		}
	}
	return false;
}