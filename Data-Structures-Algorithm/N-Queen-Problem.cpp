#include<iostream>
bool SolveNQueen(int N);

int main()
{
	//freopen("input.txt", "r", stdin);
	int TC;
	cin >> TC;
	while (TC--) {
		int N;
		cin >> N;
		SolveNQueen(N);
	}
	return 0;
}

#define ABS(x) (((x) < 0)?  (-(x)) : (x))

bool isPlaceSafe(int * pos, int N, int r, int c)
{
	for (int col = 1; col <= N; col++) {
		int row = pos[col];
		if (row != -1) {
			if ((row == r) || (col == c) || ((ABS(r - row)) == (ABS(c - col)))) {
				return false;
			}
		}
	}
	return true;
}


void fillNQueens(int *  pos, int N, int c, bool& isFound)
{
	if (c == N + 1) {
		cout << "[";
		for (int i = 1; i <= N; i++) {
			cout << pos[i] << " ";
		}
		cout << "] ";
		isFound = true;
		return;
	}
	for (int r = 1; r <= N; r++) {
		if (isPlaceSafe(pos, N, r, c)) {
			pos[c] = r;
			fillNQueens(pos, N, c + 1, isFound);
			pos[c] = -1;
		}
	}
}

bool SolveNQueen(int N)
{
	int * pos = new int[N + 1];
	for (int i = 0; i <= N; i++) {
		pos[i] = -1;
	}
	bool isFound = false;
	fillNQueens(pos, N, 1, isFound);

	if (isFound) {
		cout << endl;
	}
	else {
		cout << "-1" << endl;
	}
	delete[]pos;
	return true;
}