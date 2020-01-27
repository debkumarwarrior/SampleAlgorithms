#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution
{
	vector<string> unitdigits;
	vector<string> tensdigit;
	vector<string> elevens;
	vector<string> triples;

    public:
	Solution() {
		unitdigits.push_back("");
		unitdigits.push_back("One");
		unitdigits.push_back("Two");
		unitdigits.push_back("Three");
		unitdigits.push_back("Four");
		unitdigits.push_back("Five");
		unitdigits.push_back("Six");
		unitdigits.push_back("Seven");
		unitdigits.push_back("Eight");
		unitdigits.push_back("Nine");

		tensdigit.push_back("");
		tensdigit.push_back("");
		tensdigit.push_back("Twenty");
		tensdigit.push_back("Thirty");
		tensdigit.push_back("Forty");
		tensdigit.push_back("Fifty");
		tensdigit.push_back("Sixty");
		tensdigit.push_back("Seventy");
		tensdigit.push_back("Eighty");
		tensdigit.push_back("Ninety");

		elevens.push_back("Ten");
		elevens.push_back("Eleven");
		elevens.push_back("Twelve");
		elevens.push_back("Thirteen");
		elevens.push_back("Fourteen");
		elevens.push_back("Fifteen");
		elevens.push_back("Sixteen");
		elevens.push_back("Seventeen");
		elevens.push_back("Eighteen");
		elevens.push_back("Nineteen");

		triples.push_back("");
		triples.push_back("Thousand");
		triples.push_back("Million");
		triples.push_back("Billion");
		triples.push_back("Trillion");
	}

	string numberToWords(int n) {
        if (n == 0) {
            return "Zero";
        }
		string out = "";
		int x = 0;
		while (n > 0) {

			int dig3 = n % 1000;

			int dig0 = dig3 % 10;
			int dig1 = (dig3 / 10) % 10;
			int dig2 = (dig3 / 100) % 10;
            
            if (x > 0 && dig3 > 0) {
			    out = triples[x] + ((out != "")? " " + out : "");
            }
            x++;
			if (dig1 == 1) {
				out = elevens[dig0] + ((out != "")? " " + out : "");
			} else {
                if (dig1 > 1) {
                    if (dig0 > 0) {
                        out = tensdigit[dig1] + " " + unitdigits[dig0] + ((out != "")? " " + out : ""); 
                    } else {
                        out = tensdigit[dig1] + ((out != "")? " " + out : ""); 
                    }
                } else {
                    if (dig0 > 0) {
                        out = unitdigits[dig0] + ((out != "")? " " + out : "");
                    }                    
                }
				
			}
			if (dig2 > 0) {
				out = unitdigits[dig2] + " Hundred" +  ((out != "")? " " + out : "");
			}
			n /= 1000;
		}
		return out;
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
		cout << soln.numberToWords(n) << endl;
	}
	return 0;
}