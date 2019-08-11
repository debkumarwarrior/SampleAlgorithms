#include <iostream>
using namespace std;

int main() {
	//code
	bool sieve[10001] = { false };
	sieve[1] = true;
	sieve[2] = false;
	for (int i = 3; i <= 10000; i += 2) {
		if (sieve[i] == false) {
			for (int j = i * i; j <= 10000; j += (2 * i)) {
				sieve[j] = true;
			}
		}
	}
	/*for (int i = 1; i <= 10000; i += 2) {
		if (sieve[i] == false) {
			cout << i << " ";
		}
	}*/
	//cout << endl;
	//freopen("input.txt", "r", stdin);
	int TC = 0;
	cin >> TC;
	for (int tc = 1; tc <= TC; tc++) {
		int N = 0;
		cin >> N;
		for (int i = 3; i <= 10000; i += 2) {
			if ((sieve[i] == false) && (sieve[N - i] == false)) {
				cout << i << " " << N - i << endl;
				break;
			}
		}
	}
	return 0;
}