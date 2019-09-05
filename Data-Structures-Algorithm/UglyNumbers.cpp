//Ugly-Numbers.cpp
#include<iostream>
using namespace std;
#define MAX 10001
unsigned long long int getNthUglyNumber(int N)
{
	unsigned long long int i2 = 0, i3 = 0, i5 = 0;

	static vector<unsigned long long int> val(MAX);
    if (val[N - 1] != 0) {
        return val[N - 1];
    }
	val[0] = 1;

	for (int i = 1; i < MAX; i++)
	{
		unsigned long long int nexti2 = val[i2] * 2;
		unsigned long long int nexti3 = val[i3] * 3;
		unsigned long long int nexti5 = val[i5] * 5;

		if ((nexti2 <= nexti3) && (nexti2 <= nexti5)) {
			val[i] = nexti2;
			i2++;
		}
		if ((nexti3 <= nexti2) && (nexti3 <= nexti5)) {
			val[i] = nexti3;
			i3++;
		}
		if ((nexti5 <= nexti2) && (nexti5 <= nexti3)) {
			val[i] = nexti5;
			i5++;
		}
	}

	return val[N - 1];
}

int main()
{
	//freopen("input.txt", "r", stdin);
	int TC;
	
	cin >> TC;
	while (TC--) {
	    int N;
	    cin >> N;
		cout << getNthUglyNumber(N) << endl;;
	}
	return 0;
}