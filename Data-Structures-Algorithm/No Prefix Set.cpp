/*

Given  strings. Each string contains only lowercase letters from (both inclusive). The set of  strings is said to be GOOD SET if no string is prefix of another string else, it is BAD SET. (If two strings are identical, they are considered prefixes of each other.)

For example, aab, abcde, aabcd is BAD SET because aab is prefix of aabcd.

Print GOOD SET if it satisfies the problem requirement. 
Else, print BAD SET and the first string for which the condition fails.

Input Format 
First line contains , the number of strings in the set. 
Then next  lines follow, where  line contains  string.

Constraints 
 
 Length of the string 

Output Format 
Output GOOD SET if the set is valid. 
Else, output BAD SET followed by the first string for which the condition fails.

Sample Input00

7
aab
defgab
abcde
aabcde
cedaaa
bbbbbbbbbb
jabjjjad
Sample Output00

BAD SET
aabcde
Sample Input01

4
aab
aac
aacghgh
aabghgh
Sample Output01

BAD SET
aacghgh
Explanation 
aab is prefix of aabcde. So set is BAD SET and it fails at string aabcde.

*/

#include <iostream>
#include <string>

using namespace std;

typedef struct Trie {
  bool isEos;
  struct Trie *next[10];
} Trie;

class TrieImpl {
  Trie *trie[10];
    bool isPrefix(string s, int pos, int length, Trie * t[10]) {
        if (pos == length) {
            return false;
        }

        if (t[s[pos] - 'a'] == nullptr) {
            t[s[pos] - 'a'] = new Trie;
            Trie * tmp = t[s[pos] - 'a'];
            for (int i = 0; i < 10; i++) {
                tmp->next[i] = nullptr;
            }
            if (pos == (length - 1)) {
                t[s[pos] - 'a']->isEos = true;
            }
            else {
                t[s[pos] - 'a']->isEos = false;
            }
        }
        else {
            if (t[s[pos] - 'a']->isEos == true) {
                return true;
            }
            if (pos == (length - 1)) {
                t[s[pos] - 'a']->isEos = true;
                return true;
            }
            else {
                t[s[pos] - 'a']->isEos = false;
            }
        }
        return isPrefix(s, pos + 1, length, t[s[pos] - 'a']->next);
    }

public:
  TrieImpl() {
    for (int i = 0; i < 10; i++) {
      trie[i] = nullptr;
    }
  }
  bool isPrefix(string s) { return isPrefix(s, 0, s.length(), trie); }
};

int main() {
  //freopen("input.txt", "r", stdin);

  int n = 0;
  cin >> n;
  TrieImpl impl;
  bool isPrefix = false;
  string prefix;
  for (int i = 0; i < n; i++) {
    string s;
    cin >> s;
    if (isPrefix == false && impl.isPrefix(s) == true) {
      isPrefix = true;
      prefix = s;
    }
  }

  if (isPrefix == true) {
    cout << "BAD SET" << endl;
    cout << prefix << endl;
  } else {
    cout << "GOOD SET" << endl;
  }
  return 0;
}
