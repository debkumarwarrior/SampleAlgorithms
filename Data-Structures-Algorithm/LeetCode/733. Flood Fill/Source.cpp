#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
using namespace std;

class Solution {
	int ** dirs;
public:
	Solution() {
		dirs = new int*[4];
		for (int i = 0; i < 4; i++) {
			dirs[i] = new int[2];
		}
		dirs[0][0] = -1, dirs[0][1] = 0;
		dirs[1][0] = 1, dirs[1][1] = 0;
		dirs[2][0] = 0, dirs[2][1] = -1;
		dirs[3][0] = 0, dirs[3][1] = 1;
	}
	~Solution() {
		delete[]dirs;
	}
	bool isSafe(int N, int M, int r, int c) {
		if (r >= N) return false;
		if (c >= M) return false;

		if (r < 0) return false;
		if (c < 0) return false;

		return true;
	}

	vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor) {
		int oldColor = image[sr][sc];
		if (oldColor == newColor) {
			return image;
		}
		int n = image.size();
		if (n <= 0) {
			return image;
		}
		int m = image[0].size();
		int * queueX = new int[n * m];
		int * queueY = new int[n * m];
		int front = 0;
		int rear = 0;
		queueX[rear] = sr;
		queueY[rear] = sc;
		image[sr][sc] = newColor;

		while (front <= rear) {
			int ux = queueX[front];
			int uy = queueY[front];
			front++;

			for (int i = 0; i < 4; i++) {
				int vx = ux + dirs[i][0];
				int vy = uy + dirs[i][1];

				if (isSafe(n, m, vx, vy) && image[vx][vy] == oldColor) {
					image[vx][vy] = newColor;
					rear++;
					queueX[rear] = vx;
					queueY[rear] = vy;
				}
			}
		}
		delete[]queueX;
		delete[]queueY;
		return image;
	}
};

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	int TC;
	cin >> TC;
	Solution soln;
	for (int t = 1; t <= TC; t++) {
		int n, m;
		cin >> n >> m;
		vector<vector<int>> image(n);
		for (int i = 0; i < n; i++) {
			image[i].resize(m);
			for (int j = 0; j < m; j++) {
				cin >> image[i][j];
			}
		}

		cout << "Original Image: " << endl;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				cout << image[i][j] << " ";
			}
			cout << endl;
		}
		int sr, sc, newColor;
		cin >> sr >> sc >> newColor;
		cout << "Updating pixel(" << sr << "," << sc << ") with [" << newColor << "]"<< endl;
		soln.floodFill(image, sr, sc, newColor);
		cout << "Modified Image: " << endl;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				cout << image[i][j] << " ";
			}
			cout << endl;
		}
	}
	return 0;
}