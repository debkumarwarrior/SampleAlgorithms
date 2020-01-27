#include <iostream>
using namespace std;

class Solution {
    char * stk;
    bool isClosing(char c) {
        if (c == ')' || c == '}' || c == ']') {
            return true;
        }
        return false;
    }
    bool isPair(char a, char b) {
        if (a == '(' && b == ')') {
            return true;
        }
        if (a == '{' && b == '}') {
            return true;
        }
        if (a == '[' && b == ']') {
            return true;
        }
        return false;
    }
    public:
    bool isValid(string s) {
        stk = new char[s.length()];
        if (stk == NULL) {
            return false;
        }
        int top = -1;
        
        for (int i = 0; i < s.length(); i++) {
            if (isClosing(s[i])) {
                if (top == -1) {
                    return false;
                }
                char t = stk[top--];
                if (isPair(t,s[i])) {

                } else {
                    return false;
                }                
            } else {
                stk[++top] = s[i];
            }
        }
        if (top >= 0) {
            return false;
        } else {
            return true;
        }
    }
    ~Solution() {
        if (stk) {
            delete []stk;
            stk = NULL;            
        }
    }
};

int main()
{
	int TC;
	cin >> TC;
	Solution soln;
	while (TC--)
	{
		string s;
		cin >> s;
		cout << soln.isValid(s) << endl;
	}
	return 0;
}