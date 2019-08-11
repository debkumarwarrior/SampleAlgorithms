#include <iostream>
using namespace std;
void getMinOperations(int * p, int n);
int main() {
	//code
	//freopen("input.txt", "r", stdin);
	int TC = 0;
	cin >> TC;
	for (int tc = 1; tc <= TC; tc++) {
		int n = 0;
		cin >> n;
		int * p = new int[n];
		for (int i = 0; i < n; i++) {
			cin >> p[i];
		}
		getMinOperations(p, n);
	}
	return 0;
}
void printParenthesis(int S[100][100], int i, int j) {
	if (i == j) {
		cout << (char)('A' + (i - 1));
	} else {
		cout << "(";
		printParenthesis(S, i, S[i][j]);
		printParenthesis(S, S[i][j] + 1, j);
		cout << ")";
	}
}
void getMinOperations(int * p, int n)
{
	n--;
	const int MAX_INT = 999999999;
	int M[100][100] = { 0 };
	int S[100][100] = { 0 };

	for (int l = 2; l <= n; l++) {
		for (int i = 1; i <= n - l + 1; i++) {
			int j = i + l - 1;
			M[i][j] = MAX_INT;
			for (int k = i; k <= j; k++) {
				int q = M[i][k] + M[k + 1][j] + (p[i - 1] * p[k] * p[j]);
				if (q < M[i][j]) {
					M[i][j] = q;
					S[i][j] = k;
				}

			}
		}
	}
	printParenthesis(S, 1, n);
	cout<<endl;
}