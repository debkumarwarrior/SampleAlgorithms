/*
We're going to make our own Contacts application! The application must perform two types of operations:

add name, where  is a string denoting a contact name. This must store  as a new contact in the application.
find partial, where  is a string denoting a partial name to search the application for. It must count the number of contacts starting with  and print the count on a new line.
Given  sequential add and find operations, perform each operation in order.

Input Format

The first line contains a single integer, , denoting the number of operations to perform. 
Each line  of the  subsequent lines contains an operation in one of the two forms defined above.

Constraints

It is guaranteed that  and  contain lowercase English letters only.
The input doesn't have any duplicate  for the  operation.
Output Format

For each find partial operation, print the number of contact names starting with  on a new line.

Sample Input

4
add hack
add hackerrank
find hac
find hak
Sample Output

2
0
Explanation

We perform the following sequence of operations:

Add a contact named hack.
Add a contact named hackerrank.
Find and print the number of contact names beginning with hac. There are currently two contact names in the application and both of them start with hac, so we print  on a new line.
Find and print the number of contact names beginning with hak. There are currently two contact names in the application but neither of them start with hak, so we print  on a new line.

*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

/*
 * Complete the contacts function below.
 */
typedef struct Trie {
    bool isEnd;
    int count;
    struct Trie * next[26];
}Trie;

class TrieImpl {
    Trie * arr[26];
    void insert(string s, int pos, int len, Trie * t[26]) {
        if (pos == len) {
            return;
        }
        if (t[s[pos] - 'a'] == nullptr) {
            t[s[pos] - 'a'] = new Trie();
            Trie * tmp = t[s[pos] - 'a'];
            for (int i = 0; i < 26; i++) {
                tmp->next[i] = nullptr;
            }
            tmp->count = 1;
            if (pos == len - 1) {
                t[s[pos] - 'a']->isEnd = true;
            }
            else {
                t[s[pos] - 'a']->isEnd = false;
            }
        } else {
            t[s[pos] - 'a']->count += 1;
        }
        insert(s, pos + 1, len, t[s[pos] - 'a']->next);
    }

    int query(string s, int pos, int length, Trie * t[26]) {
        if (pos == length - 1) {
            if (t[s[pos] - 'a'] == nullptr) {
                return 0;
            }
            else {
                return t[s[pos] - 'a']->count;
            }
        }
        else {
            if (t[s[pos] - 'a'] == nullptr) {
                return 0;
            } else {
                return query(s, pos + 1, length, t[s[pos] - 'a']->next);
            }
        }
    }

public:
    TrieImpl () {
        for (int i = 0; i < 26; i++) {
            arr[i] = nullptr;
        }
    }
    void add(string s) {
        if (s.length() == 0) {
            return;
        }
        insert(s, 0, s.length(), arr);
    }

    int find(string s) {
        if (s.length() == 0) {
            return 0;
        }
        return query(s, 0, s.length(), arr);
    }
};
vector<int> contacts(vector<vector<string>> queries) {
    /*
    * Write your code here.
    */
    vector<int> result;
    TrieImpl impl;
    int find = 0;
    for (int i = 0; i < queries.size(); i++) {
        if (queries[i][0] == "add") {
            impl.add(queries[i][1]);
        } else {
            find += 1;
            result.resize(find);
            result[find - 1] = impl.find(queries[i][1]);
        }
    }
    return result;

}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int queries_rows;
    cin >> queries_rows;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<vector<string>> queries(queries_rows);
    for (int queries_row_itr = 0; queries_row_itr < queries_rows; queries_row_itr++) {
        queries[queries_row_itr].resize(2);

        for (int queries_column_itr = 0; queries_column_itr < 2; queries_column_itr++) {
            cin >> queries[queries_row_itr][queries_column_itr];
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    vector<int> result = contacts(queries);

    for (int result_itr = 0; result_itr < result.size(); result_itr++) {
        fout << result[result_itr];

        if (result_itr != result.size() - 1) {
            fout << "\n";
        }
    }

    fout << "\n";

    fout.close();

    return 0;
}
