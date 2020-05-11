#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
using namespace std;

class Solution {
	bool isSafe(vector<vector<char>> board, int N, int boxsize, char v, int r, int c) {
		for (int i = 0; i < N; i++) {
			if (board[i][c] == v) {
				return false;
			}
			if (board[r][i] == v) {
				return false;
			}
		}

		int sr = (r / boxsize) * boxsize, er = ((r / boxsize) + 1) * boxsize;
		int sc = (c / boxsize) * boxsize, ec = ((c / boxsize) + 1) * boxsize;

		for (int i = sr; i < er; i++) {
			for (int j = sc; j < ec; j++) {
				if (board[i][j] == v) {
					return false;
				}
			}
		}
		return true;
	}
	bool findEmpty(vector<vector<char>>& board, int N, int& r, int& c) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (board[i][j] == '.') {
					r = i, c = j;
					return true;
				}
			}
		}
		return false;
	}
	bool solveSudoku(vector<vector<char>>& board, int N, int boxsize) {
		int r = -1, c = -1;
		if (findEmpty(board, N, r, c) == false) {
			return true;
		}
		for (char v = '1'; v <= '0' + N; v++) {
			if (isSafe(board, N, boxsize, v, r, c)) {
				board[r][c] = v;
				if (solveSudoku(board, N, boxsize)) {
					return true;
				}
				board[r][c] = '.';
			}
		}
		return false;
	}
public:
	void solveSudoku(vector<vector<char>>& board) {
		int N = board.size();
		int boxsize = 3;
		solveSudoku(board, N, boxsize);
	}
};

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int T;
	cin >> T;
	Solution soln;
	for (int tc = 1; tc <= T; tc++) {
		vector<vector<char>> board(9);
		for (int i = 0; i < 9; i++) {
			board[i].resize(9);
			for (int j = 0; j < 9; j++) {
				cin >> board[i][j];
			}
		}

		cout << "Original board: " << endl;
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				cout << board[i][j] << " ";
			}
			cout << endl;
		}
		soln.solveSudoku(board);
		cout << endl << "Solved board: " << endl;
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				cout << board[i][j] << " ";
			}
			cout << endl;
		}
		cout << endl << endl;
	}
	return 0;
}