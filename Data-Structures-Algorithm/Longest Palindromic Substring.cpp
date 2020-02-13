class Solution {
	inline int max(int a, int b) {
		return (a > b) ? a : b;
	}
	void getLength(string s, int l, int r, int& ansl, int& ansr, int& maxL) {
		while ((l >= 0) && (r < s.length()) && (s[l] == s[r])) {
			int len = r - l + 1;
			if (len > maxL) {
				maxL = len;
				ansl = l, ansr = r;
			}
			l--, r++;
		}
	}
public:
	string longestPalindrome(string s) {
        if (s.length() == 0) {
            return string("");
        }
		int maxL = 0, ansl, ansr;
		string ans;
		for (int i = 0; i < s.length(); i++) {
			getLength(s, i, i, ansl, ansr, maxL);
			getLength(s, i, i + 1, ansl, ansr, maxL);
		}
		return s.substr(ansl, ansr - ansl + 1);
	}
};
