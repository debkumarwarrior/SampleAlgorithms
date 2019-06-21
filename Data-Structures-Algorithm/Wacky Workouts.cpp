/*

The government of virtualBit believes that the health of its citizens is the highest priority. It has devised an N-day health plan. During these N days, the citizens are encouraged to go to the gym for workouts.

A person may or may not go to the gym on any day. The people of virtualBit are a lazy lot, and they don't want to go to the gym for more than one consecutive day. Given the number of days N, print the number of ways the N-day plan can be completed.

Note that it is possible to not go to the gym on any day at all and still complete the plan.

Input

The first line contains T, the number of test cases.

Each test case contains a number N denoting the number of days.

Output

Each test case contains a single number denoting the number of ways by which the N-day plan may be completed.

Output your answer modulo 109+7.
*/

#include <iostream>
using namespace std;
typedef unsigned long long int ull;
ull fib(ull n);
void power(ull ans[2][2], ull fib[2][2], ull n, ull m);
 
int main() {
	//freopen("input.txt", "r", stdin);
	int T = 0;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		ull n = 0;
		cin >> n;
		cout << fib(n) << endl;
	}
	return 0;
}
 
ull fib(ull n) {
	ull ans[2][2] = { 0 };
	ull fib[2][2] = { { 1, 1 }, { 1, 0 } };
 
	power(ans, fib, n - 1, 1000000007);
	return ((ans[0][0] * 2) + (ans[0][1] * 1)) % 1000000007;
}
 
void power(ull ans[2][2], ull fib[2][2], ull n, ull m) {
	ans[0][0] = 1;
	ans[0][1] = 0;
	ans[1][0] = 0;
	ans[1][1] = 1;
 
	while (n > 0) {
		if (n & 1) {
			ull tmp[2][2] = { 0 };
			tmp[0][0] = ((ans[0][0] * fib[0][0]) + (ans[0][1] * fib[1][0])) % m;
			tmp[0][1] = ((ans[0][0] * fib[0][1]) + (ans[0][1] * fib[1][1])) % m;
			tmp[1][0] = ((ans[1][0] * fib[0][0]) + (ans[1][1] * fib[1][0])) % m;
			tmp[1][1] = ((ans[1][0] * fib[0][1]) + (ans[1][1] * fib[1][1])) % m;
 
			ans[0][0] = tmp[0][0];
			ans[0][1] = tmp[0][1];
			ans[1][0] = tmp[1][0];
			ans[1][1] = tmp[1][1];
		}
		ull tmp[2][2] = { 0 };
		tmp[0][0] = ((fib[0][0] * fib[0][0]) + (fib[0][1] * fib[1][0])) % m;
		tmp[0][1] = ((fib[0][0] * fib[0][1]) + (fib[0][1] * fib[1][1])) % m;
		tmp[1][0] = ((fib[1][0] * fib[0][0]) + (fib[1][1] * fib[1][0])) % m;
		tmp[1][1] = ((fib[1][0] * fib[0][1]) + (fib[1][1] * fib[1][1])) % m;
 
		fib[0][0] = tmp[0][0];
		fib[0][1] = tmp[0][1];
		fib[1][0] = tmp[1][0];
		fib[1][1] = tmp[1][1];
		n = n / 2;
	}
}