/*
Creatnx now wants to decorate his house by flower pots. He plans to buy exactly  ones. He can only buy them from Triracle's shop. There are only two kind of flower pots available in that shop. The shop is very strange. If you buy  flower pots of kind 1 then you must pay A * X^2 + B* Y^2 and  if you buy  flower pots of kind 2. Please help Creatnx buys exactly  flower pots that minimizes money he pays.

Input Format

The first line contains a integer  denoting the number of test cases.

Each of test case is described in a single line containing three space-separated integers .

Sample Input:
2
5 1 2
10 2 4

Sample output:
17
134

// Sample code to perform I/O:
 
#include <iostream>
 
using namespace std;
 
int main() {
	int num;
	cin >> num;										// Reading input from STDIN
	cout << "Input number is " << num << endl;		// Writing output to STDOUT
}
 
// Warning: Printing unwanted or ill-formatted data to output will cause the test cases to fail
*/
 
// Write your code here
#include <iostream>
using namespace std;
 
int main() {
	int T = 0;
	cin >> T;
	for (int t = 0; t < T; t++) {
	    long long n, a, b;
	    cin >> n >> a >> b;
	    long long x1 = ((b * n) / (a + b));
	    long long x2 = ((b * n) / (a + b)) + 1;
	    
	    long long val1 = ((a * x1 * x1) + (b * (n - x1) * (n - x1)));
	    long long val2 = ((a * x2 * x2) + (b * (n - x2) * (n - x2)));
	    cout << ((val1 < val2)? val1 : val2) << endl;
	}
	return 0;
}