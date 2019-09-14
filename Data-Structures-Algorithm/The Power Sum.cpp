/*
Find the number of ways that a given integer, , can be expressed as the sum of the  powers of unique, natural numbers.

For example, if  and , we have to find all combinations of unique squares adding up to . The only solution is .

Function Description

Complete the powerSum function in the editor below. It should return an integer that represents the number of possible combinations.

powerSum has the following parameter(s):

X: the integer to sum to
N: the integer power to raise numbers to

*/

#include <bits/stdc++.h>

using namespace std;

// Complete the powerSum function below.
int power(int a, int b)
{
    int c = 1;
    while (b) {
        if ((b % 2) == 1) {
            c *= a;
        }
        a *= a;
        b /= 2;
    }
    return c;
}



int getNumber(int X, int N, int d)
{
    if (X == 0) {
        return 1;
    }
    if (X < 0) {
        return 0;
    }
    int cnt = 0;
    for (int i = d + 1; i <= X; i++)
    {
        int pow = power(i, N);
        if (pow > X) {
            break;
        }
        cnt += getNumber(X - pow, N, i);
    }
    return cnt;
}

int powerSum(int X, int N)
{
    return getNumber(X, N, 0);
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int X;
    cin >> X;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    int N;
    cin >> N;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    int result = powerSum(X, N);

    fout << result << "\n";

    fout.close();

    return 0;
}
