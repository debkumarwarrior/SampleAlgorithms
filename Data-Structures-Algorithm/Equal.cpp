#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

// Complete the equal function below.
long long equal(vector<int> arr)
{
    int min = arr[0];
    for (auto i : arr) {
        min = (i < min) ? i : min;
    }
    long long min_steps = 0x7FFFFFFFFFFFFFFF;
    int k = 0;
    while (k <= 5) {
        int steps = 0;
        for (int i = 0; i < arr.size(); i++) {
            int diff_i = arr[i] - (min - k);
            int a_i = diff_i / 5;
            int b_i = (diff_i % 5) / 2;
            int c_i = ((diff_i % 5) % 2) / 1;
            steps += a_i + b_i + c_i;
        }
        min_steps = (steps < min_steps) ? steps : min_steps;
        k++;
    }
    return min_steps;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int t;
    cin >> t;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int t_itr = 0; t_itr < t; t_itr++) {
        int n;
        cin >> n;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        string arr_temp_temp;
        getline(cin, arr_temp_temp);

        vector<string> arr_temp = split_string(arr_temp_temp);

        vector<int> arr(n);

        for (int i = 0; i < n; i++) {
            int arr_item = stoi(arr_temp[i]);

            arr[i] = arr_item;
        }

        int result = equal(arr);

        fout << result << "\n";
    }

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
