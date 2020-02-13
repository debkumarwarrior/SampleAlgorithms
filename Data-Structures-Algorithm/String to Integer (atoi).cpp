class Solution {
public:
	int myAtoi(string str)
	{
		int sign = 1;
		string::iterator it = str.begin();
		while (it != str.end() && *it == ' ') { it++; }

		if (*it == '-') {
			sign = -1;
			it++;
		}
		else if (*it == '+') {
			sign = 1;
			it++;
		}
		int result = 0;
		for (; it != str.end(); it++) {
			if (result > 214748364)  {
				if (*it >= '0' && *it <= '9') {
					return (sign == -1) ? INT_MIN : INT_MAX;
				}
				else {
					break;
				}
			}
			else if (result == 214748364) {
				if (*it >= '0' && *it <= '7') {
					result *= 10;
					result += (*it) - '0';
				}
				else if (*it == '9' || *it == '8') {
					if (sign == -1) {
						return INT_MIN;
					}
					else {
						return INT_MAX;
					}
				}
				else {
					break;
				}
			}
			else {
				if (*it >= '0' && *it <= '9') {
					result *= 10;
					result += (*it) - '0';
				}
				else {
					break;
				}
			}
		}
		return (result * sign);
	}
};
