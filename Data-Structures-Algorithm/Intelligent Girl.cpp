/*
Soumika has a string S and its starting index is 1. The string S consists of characters from \(1-9\). As she is very intelligent, she wants to test his brother Vinay Tendulkar. She asked her brother Vinay Tendulkar to count the number of even numbered characters ( i.e \(2,4,6,8\) ) for every index i \( (1 \le i \le | S|)\). For an index i, the result should be calculated from i to the end of the string. As Vinay doesn't know about programming, he wants you to help him find the solution.
*/

#include <iostream>
#include <string>
 
using namespace std;
 
int main() {
	//freopen("input.txt", "r", stdin);
 
	string s;
	cin >> s;
 
	int * c = new int[s.length() + 1];
 
	c[0] = 0;
	for (unsigned int i = 0; i < s.length(); i++) {
		if ((s[i] == '2') || (s[i] == '4') || (s[i] == '6') || (s[i] == '8')) {
			c[i + 1] = c[i] + 1;
		} else {
			c[i + 1] = c[i];
		}
	}
 
	for (unsigned int i = 1; i <= s.length(); i++) {
		cout << c[s.length()] - c[i - 1] << " ";
	}
	cout << endl;
	return 0;
}