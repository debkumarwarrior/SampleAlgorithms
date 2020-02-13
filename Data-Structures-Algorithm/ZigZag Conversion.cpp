class Solution {
public:
	string convert(string s, int numRows) {
		if (numRows == 1) {
			return s;
		}        
		string * sr = new string[numRows];
		bool inc = false;
		int ctr = 0;
		for (int i = 0; i < numRows; i++) {
			sr[i] = "";
		}
		for (string::iterator it = s.begin(); it != s.end(); it++) {
			sr[ctr] += *it;
			if ((ctr == (numRows - 1)) || (ctr == 0)) {
				inc = (inc) ? false : true;
			}
			(inc) ? ctr++ : ctr--;
		}

		string result = "";
		for (int i = 0; i < numRows; i++) {
			for (string::iterator it = sr[i].begin(); it != sr[i].end(); it++) {
				result += *it;
			}
		}
		delete[]sr;
		return result;
	}
};
