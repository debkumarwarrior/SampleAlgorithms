#include <iostream>
using namespace std;
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.size() <= 0) {
            return 0;
        }
        int mProfit = 0;
        int minVal = prices[0];
        
        for (auto p : prices) {
            mProfit = (mProfit > (p - minVal))? mProfit : p - minVal;
            minVal = (minVal < p)? minVal : p;
        }
        return mProfit;
    }
};

int main()
{
	int TC;
	cin >> TC;
	Solution soln;
	while (TC--)
	{
		int n;
		cin >> n;
		vector <int> stock(n);
		for (int i = 0; i < n; i++)
		{
			cin >> stock[i];
		}
		cout << soln.maxProfit(stock) << endl;
	}
	return 0;
}