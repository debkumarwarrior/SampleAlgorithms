#include <iostream>
using namespace std;
typedef struct trap
{
	int val;
	int maxL;
	int maxR;
}Trap;
#define MAX(a,b) (((a) > (b))? (a) : (b))
#define MIN(a,b) (((a) < (b))? (a) : (b))
int main() {
	//code
	//freopen("input.txt", "r", stdin);
	int TC = 0;
	cin >> TC;
	for (int tc = 1; tc <= TC; tc++) {
		int N = 0;
		cin >> N;
		Trap * arr = new Trap[N];
		for (int i = 0; i < N; i++) {
			cin >> arr[i].val;
		}

		int mL = arr[0].val;
		int mR = arr[N - 1].val;
		for (int i = 0, j= N - 1; i < N; i++, j--) {
			mL = MAX(arr[i].val, mL);
			mR = MAX(arr[j].val, mR);
			arr[i].maxL = mL;
			arr[j].maxR = mR;

		}

		int totW = 0;
		for (int i = 0, j = N - 1; i < N; i++, j--) {
			int water = MIN(arr[i].maxL, arr[i].maxR) - arr[i].val;
			totW += (water < 0) ? 0 : water;
		}
		cout << totW << endl;
		delete[]arr;

	}
	return 0;
}