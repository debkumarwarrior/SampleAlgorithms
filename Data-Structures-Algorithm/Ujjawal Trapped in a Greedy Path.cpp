/*

You are given n∗m matrix and in each cell there are some coins given. Now you are asked to find maximum number of coins you can get by travelling from top to bottom following some rules.

Note:

You can start from any column but only from 1st row.
From cell ( i , j ) you can move only to ( i+1, j-1 ) or (i+1, j+1) if i+1<=n and j+1<=m and j−1>0 . (Using 1-based indexing)
You can end at any column but only on last row.
You can collect coins from cell (i,j) if and only if  a%2==1 
 a = gcd(fib(ji),fib(ij)) where fib denotes fibonacci sequence.
fib(0)=0 ,  fib(1)=1 and fib(i)=fib(i−1)+fib(i−2),for:i>1 
 Use 1-based indexing else you will get wrong ans.
You have to find maximum number of coins you can collect.

As Ujjawal was not able to solve this problem , he asks for your help.

Constraints:

0<r<1000

0<c<1000

value of coin at each cell 0<coins<109

Input format:

First line contains r and c : number of rows and columns.

Then it contains r∗c matrix containing coins.

*/

#include <iostream>
using namespace std;
typedef long long int ll;
 
ll power(int a, int b, int M) {
	ll ans = 1;
	while (b > 0) {
		if (b & 1) {
			ans = (ans * a) % M;
		}
		a = (a * a) % M;
		b = b / 2;
	}
	return ans;
}
 
bool canCollectCoins(int r, int c) {
	if (((r % 3) == 0) && ((c % 3) == 0)) {
		return false;
	}
	return true;
}
 
bool isValidNode(int R, int C, int r, int c) {
	if ((r <= 0) || (r > R)) {
		return false;
	}
	if ((c <= 0) || (c > C)) {
		return false;
	}
 
	return true;
}
// 112295787551
// 112218329306
 
ll arr[1024][1024] = { 0 };
ll  dp[1024][1024] = { 0 };
 
int main() {
	//freopen("input.txt", "r", stdin);
 
	int R = 0, C = 0;
	cin >> R >> C;
 
	for (int r = 1; r <= R; r++) {
		for (int c = 1; c <= C; c++) {
			cin >> arr[r][c];
		}
	}
 
	for (int r = R; r >= 1; r--) {
		for (int c = 1; c <= C; c++) {
			ll val1 = -1;
			ll val2 = -1;
			dp[r][c] = 0;
			if (isValidNode(R, C, r + 1, c - 1)){
				val1 = dp[r + 1][c - 1];
			}
			if (isValidNode(R, C, r + 1, c + 1)){
				val2 = dp[r + 1][c + 1];
			}			
			
			if (canCollectCoins(r, c)) {
				dp[r][c] = arr[r][c];
			}
			if (val1 != -1 || val2 != -1) {
				dp[r][c] += (val1 > val2) ? val1 : val2;
			}
		}
	}
 
	ll maxVal = dp[1][1];
	for (int c = 2; c <= C; c++) {
		maxVal = (maxVal > dp[1][c]) ? maxVal : dp[1][c];
	}
	cout << maxVal << endl;
	return 0;
}