#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
using namespace std;
class Solution
{
	void transform(vector<vector<int>>& img, int s, int e) {
		if (s == e) {
			return;
		}
		for (int i = 0; i < (e - s); i++) {
			int x = img[s][s + i];
			img[s][s + i] = img[e - i][s];
			img[e - i][s] = img[e][e - i];
			img[e][e - i] = img[s + i][e];
			img[s + i][e] = x;
		}
	}
public:
	void rotate(vector<vector<int>>& matrix) {
		int n = matrix.size();
		for (int s = 0, e = n - 1; s < e; s++, e--) {
			transform(matrix, s, e);
		}
	}
 };

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int TC;
	cin >> TC;
	Solution soln;
	for (int tc = 1; tc <= TC; tc++) {
		int n;
		cin >> n;
		vector<vector<int>> img(n);
		for (int i = 0; i < n; i++) {
			img[i].resize(n);
			for (int j = 0; j < n; j++) {
				cin >> img[i][j];
			}
		}

		cout << "#" << tc << ":" << endl << "Original :" << endl;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cout << img[i][j] << " ";
			}
			cout << endl;
		}
		cout << endl << "Rotated :" << endl;
		soln.rotate(img);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cout << img[i][j] << " ";
			}
			cout << endl;
		}
		cout << endl;
	}
	return 0;
}