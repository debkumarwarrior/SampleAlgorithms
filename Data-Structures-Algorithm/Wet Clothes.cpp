/*

We have  completely wet clothes out under sunshine waiting to become dry. we are now at second  and it's raining. It's going to rain again on seconds  and after each rain clothes will be completely wet again. Cloth number  needs  seconds to become dry. We can go out and collect all dry clothes at any moment but can't do this more than  times. What is the maximum number of clothes we can collect until second ? Note that the duration of each rain is almost zero, so we can ignore it. Also collecting clothes does not take any time from us.

Input format

First line of input contains three integers  (, ) respectively. In the second line will be  increasing numbers denoting  (). In the Last line will have  numbers denoting  ().

Output format

In a single line print maxmimum number of clothes we can collect.

*/

// Write your code here
#include <iostream>
 
using namespace std;
 
int main() {
	int n, m , g;
	cin >> n >> m >> g;
	int * t = new int[n];
	cin >> t[0];
	int maxtime =-1;
	for (int i = 1; i < n; i++) {
	    cin >> t[i];
	    if (maxtime < (t[i] - t[i - 1])) {
	        maxtime = t[i] - t[i - 1];
	    }
	}
	int cnt = 0;
	for (int i = 0; i < m; i++) {
	    int x = 0;
	    cin >> x;
	    
	    if (x <= maxtime) {
	        cnt++;
	    }
	}
	delete []t;
	cout << cnt << endl;
	
	return 0;
}