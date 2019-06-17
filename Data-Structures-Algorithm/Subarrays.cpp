You are given an array  of length . You are required to select  non-intersecting subarrays. The cost will be considered as the sum of all numbers in these subarrays divided by . Your task is to maximize this cost.

A subarray of  is a non-empty sequence obtained by deleting a prefix and/or a suffix from the sequence . The prefix or suffix can be empty which means that  is considered to be a subarray of . There are subarrays in an array of length .

You can select no subarrays () and the cost is considered to be equal to . 

If there are more than one solutions that contain the same cost, then select the one that contains the highest .
// Write your code here
#include <iostream>
 
using namespace std;
 
#define MAX(a, b) (((a) > (b))? (a) : (b))
int main() {
	int n;
	cin >> n;										// Reading input from STDIN
	int * a = new int[n];
	cin >> a[0];
	int maxVal = 0;
	int maxCount = 0;
 
	for (int i = 1; i < n; i++) {
	    cin >> a[i];
	    
	    a[i] = MAX(a[i], a[i] + a[i - 1]);
	    
	    if (maxVal < a[i]) {
	        maxVal = a[i];
	    }
	}
	
	for (int i = 0; i < n; i++) {
	    if (maxVal == a[i]) {
	        maxCount++;
	    }
	}
	delete []a;
	cout << maxVal << " " << maxCount << endl;
	return 0;
}