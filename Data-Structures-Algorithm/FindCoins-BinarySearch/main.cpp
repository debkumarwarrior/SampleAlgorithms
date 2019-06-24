#include <iostream>
#include <cstdlib>

using namespace std;

int arr[1024] = { 0 };

typedef struct Result {
	int tenIndex;
	int thirtyIndex;
}Result;

extern Result findCoins(int N);

int queries = 0;

int weigh(int leftNum, int * left, int rightNum, int * right) {
	bool visit[1024] = { false };
	int lwt = 0, rwt = 0;
	
	queries++;

	for (int i = 1; i <= leftNum; i++) {
		int idx = left[i];
		visit[idx] = true;
		lwt += arr[idx];
	}

	for (int i = 1; i <= rightNum; i++) {
		int idx = right[i];
		if (visit[idx] == true) {
			return -2;
		}
		rwt += arr[idx];
	}

	if (lwt < rwt) return -1;
	if (lwt > rwt) return 1;
	return 0;
}

int kase(int N)
{
	queries = 0;
	int success = 1;
	for (int i = 1; i <= N; i++) {
		arr[i] = 20;
	}

	int tenIndex = -1, thirtyIndex = -1;
	while (tenIndex == thirtyIndex) {
		tenIndex = (rand() % N) + 1;
		thirtyIndex = (rand() % N) + 1;
	}

	arr[tenIndex] = 10;
	arr[thirtyIndex] = 30;
	//cout << "10-Index: [" << tenIndex << "] 30-Index: [" << thirtyIndex << "]" << endl;
	/* cout << "Generated" << endl;
	for (int i = 1; i <= N; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;*/
	Result res = findCoins(N);
	if ((res.tenIndex == tenIndex) && (res.thirtyIndex == thirtyIndex) && (queries < 40)) {
		//cout << "Validation success." << endl;
		success = 1;
	} else {
		//cout << "Validation failed." << endl;
		success = 0;
	}

	return success;
}

int main() {

	freopen("input.txt", "r", stdin);
	
	int T = 0;
	cin >> T;

	for (int tc = 1; tc <= T; tc++) {
		int N = 0;
		cin >> N;
		cout << "#" << tc << " Samples: " << N << " Success: " << kase(N) << endl;
	}
	return 0;
}
