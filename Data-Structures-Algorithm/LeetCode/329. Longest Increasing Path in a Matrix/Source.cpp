#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
using namespace std;

class Solution {
	int dirs[4][2] = { {-1,0},{0, -1}, { 1, 0}, {0, 1} };
	bool isValid(int R, int C, int r, int c) {
		if (r < 0) {
			return false;
		}
		if (c < 0) {
			return false;
		}
		if (r >= R) {
			return false;
		}
		if (c >= C) {
			return false;
		}
		return true;
	}

	int max_val(int a, int b) {
		return (a > b) ? a : b;
	}

	int get_longest_path(int r, int c, int R, int C, vector<vector<int>>& dp, vector<vector<int>>& matrix) {
		if (dp[r][c] != 0) {
			return dp[r][c];
		}

		int max_len = 1;

		for (int d = 0; d < 4; d++) {
			int newr = r + dirs[d][0];
			int newc = c + dirs[d][1];

			if (isValid(R, C, newr, newc) && (matrix[r][c] < matrix[newr][newc])) {
				max_len = max_val(max_len, 1 + get_longest_path(newr, newc, R, C, dp, matrix));
			}
		}

		return (dp[r][c] = max_len);

	}

public:
	int longestIncreasingPath(vector<vector<int>>& matrix) {
		int M = matrix.size();
		if (M <= 0) {
			return 0;
		}
		int N = matrix[0].size();
		if (N <= 0) {
			return 0;
		}
		vector<vector<int>> dp(M, vector<int>(N, 0));
		int max_len = 0;
		for (int r = 0; r < M; r++) {
			for (int c = 0; c < N; c++) {
				max_len = max_val(max_len, get_longest_path(r, c, M, N, dp, matrix));
  			}
		}

		return max_len;
	}
};

int main() {
	freopen("input.txt", "r", stdin);
	int TC;
	cin >> TC;

	for (int test = 1; test <= TC; test++) {
		int M, N;
		cin >> M >> N;
		vector<vector<int>> matrix(M, vector<int>(N, 0));
		for (int i = 0; i < M; i++) {
			for (int j = 0; j < N; j++) {
				cin >> matrix[i][j];
			}
		}

		Solution soln;
		cout << "#" << test << " " << soln.longestIncreasingPath(matrix) << endl;
	}
	return 0;
}