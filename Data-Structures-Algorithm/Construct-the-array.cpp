#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

// Complete the countArray function below.
const long MODULO = (1000000007);
long countArray(int n, int k, int x) {
    // Return the number of ways to fill in the array.
    vector<vector<long long int>> dp(n);
    dp[0].resize(2);
    dp[0][0] = 1;
    dp[0][1] = 0;
    for (int i = 1; i < n; i++) {
        dp[i].resize(2);
        dp[i][0] = (dp[i - 1][1] * (k - 1)) % MODULO;
        dp[i][1] = (dp[i - 1][0] + (dp[i - 1][1] * (k - 2))) % MODULO;
    }
    if (x == 1) {
        return dp[n - 1][0] % MODULO;
    }
    else {
        return dp[n - 1][1] % MODULO;
    }

}
int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string nkx_temp;
    getline(cin, nkx_temp);

    vector<string> nkx = split_string(nkx_temp);

    int n = stoi(nkx[0]);

    int k = stoi(nkx[1]);

    int x = stoi(nkx[2]);

    long answer = countArray(n, k, x);

    fout << answer << "\n";

    fout.close();

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}
